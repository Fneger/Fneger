#include "st_logger.h"
#include <QTextStream>
#include "zpmainframe.h"
namespace STMsgLogger{
    st_logger::st_logger()
        :m_isRunning(false)
	{
		m_pLogFile = 0;
		m_bUseLogFile = true;
		m_nLogLevel = 2;
        m_nMaxFileSize = 20*1024*1024;
        m_zpMainFrame = nullptr;
        m_currentBuffer.reset(new QByteArray());
        m_currentBuffer->resize(S_BUFFER_SIZE);
        m_currentBuffer->truncate(0);
        m_nextBuffer.reset(new QByteArray());
        m_nextBuffer->resize(S_BUFFER_SIZE);
        m_nextBuffer->truncate(0);
	}

    void st_logger::setZPMainFrame(ZPMainFrame *ui)
    {
        m_zpMainFrame = ui;
    }

	void st_logger::setMaxFileSize(int nSize)
	{
		if (nSize >=1024*1024 && nSize <=1024*1024*1024)
			m_nMaxFileSize = nSize;
	}
	int st_logger::maxFileSize() const
	{
		return m_nMaxFileSize;
	}
	int st_logger::logLevel() const
	{
		return m_nLogLevel;
	}
	void st_logger::setLogLevel(int lv)
	{
		if (lv >=0 && lv <=3)
			m_nLogLevel = lv;
	}

	bool st_logger::CreateNewLogFile(QCoreApplication * app)
    {
        bool res = false;
        QDateTime dtmCur = QDateTime::currentDateTime();
        m_currLogFileName = app->applicationDirPath() + "/Log/";
        QDir dir;
        dir.mkpath(m_currLogFileName);
        m_currLogFileName += app->applicationName() + "_debug.log";
        if (m_pLogFile)
        {
            if (m_pLogFile->isOpen()==true)
            {
                QString bakLog = m_currLogFileName + ".bak";
                QFile file(bakLog);
                if(file.exists())
                    file.remove();
                m_pLogFile->rename(bakLog);
                m_pLogFile->close();
            }
            m_pLogFile->deleteLater();
            m_pLogFile = 0;
        }
        m_pLogFile = new QFile (m_currLogFileName);
        if (m_pLogFile)
        {
            if (m_pLogFile->open(QIODevice::WriteOnly | QIODevice::Append)==false)
            {
                m_pLogFile->deleteLater();
                m_pLogFile = 0;
            }
            else
                res = true;
        }
        return res;
	}
	void st_logger::MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
		switch (type) {
		case QtDebugMsg:
			if (m_nLogLevel < 3)
            {
				return;
			}
			break;
		case QtWarningMsg:
			if (m_nLogLevel < 2)
            {
				return;
			}
			break;
		case QtCriticalMsg:
			if (m_nLogLevel < 1)
            {
				return;
			}
			break;
		case QtFatalMsg:
			if (m_nLogLevel < 0)
            {
				return;
			}
			break;
		default:
			if (m_nLogLevel < 3)
            {
				return;
			}
			break;
        }
		QDateTime dtmCur = QDateTime::currentDateTime().toUTC();

		QString strMsg ;
        strMsg += dtmCur.toString("yyyy-MM-dd HH:mm:ss.zzz");
        strMsg += " > ";
		switch (type) {
		case QtDebugMsg:
			strMsg += QString("Debug   :");
			break;
		case QtWarningMsg:
			strMsg += QString("Warning :");
			break;
		case QtCriticalMsg:
			strMsg += QString("Critical:");
			break;
		case QtFatalMsg:
			strMsg += QString("Fatal   :");
			break;
		default:
			strMsg += QString("Unknown :");
			break;
		}
        strMsg.append(msg + "\n");
#if 0
        if(m_zpMainFrame != nullptr)
            m_zpMainFrame->printLog(strMsg);

		QTextStream stream(m_pLogFile);
		stream << strMsg;
		stream.flush();
		if (m_pLogFile->pos()>=m_nMaxFileSize)
			m_bUseLogFile = CreateNewLogFile(QCoreApplication::instance());
#endif
        MessageAppend(strMsg);

	}

    void st_logger::MessageAppend(const QString &msg)
    {
        bool isFull = false;
        {
            boost::mutex::scoped_lock lock(m_logMutex);
            if(m_currentBuffer->size() > msg.length())
                m_currentBuffer->append(msg);
            else
            {
                m_buffers.push_back(std::move(m_currentBuffer));
                if(m_nextBuffer)
                    m_currentBuffer = std::move(m_nextBuffer);
                else
                {
                    m_currentBuffer.reset(new QByteArray());
                    m_currentBuffer->resize(S_BUFFER_SIZE);
                }
                m_currentBuffer->append(msg);
                isFull = true;
            }
        }
        if(isFull)
            m_logCondi.notify_one();
    }

    void st_logger::start()
    {
        m_logThread.reset(new boost::thread(boost::bind(&st_logger::run, this)));
    }

    void st_logger::stop()
    {
        m_isRunning = false;
        m_logThread->join();
    }

    void st_logger::run()
    {
        m_isRunning = true;

        if (m_pLogFile==0)
        {
            if (m_bUseLogFile==true)
                m_bUseLogFile = CreateNewLogFile(QCoreApplication::instance());
            if (m_pLogFile==0)
            {
                return;
            }
        }
        BufferPtr newBuffer1(new QByteArray);
        newBuffer1->resize(S_BUFFER_SIZE);
        newBuffer1->truncate(0);
        BufferPtr newBuffer2(new QByteArray);
        newBuffer2->resize(S_BUFFER_SIZE);
        newBuffer2->truncate(0);
        BufferVector buffersToWrite;
        buffersToWrite.reserve(16);
        while (m_isRunning) {
            {
                boost::mutex::scoped_lock lock(m_logMutex);
                if(m_buffers.empty())
                    m_logCondi.timed_wait(lock,  boost::get_system_time() + boost::posix_time::seconds(3));
                m_buffers.push_back(std::move(m_currentBuffer));
                m_currentBuffer = std::move(newBuffer1);
                buffersToWrite.swap(m_buffers);
                if (!m_nextBuffer)
                {
                    m_nextBuffer = std::move(newBuffer2);
                }
            }

            QTextStream stream(m_pLogFile);
            if (buffersToWrite.size() > 25)
            {
              char buf[256];
              snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
                       QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz").toStdString().c_str(),
                       buffersToWrite.size()-2);
              fputs(buf, stderr);
              stream << buf;
              buffersToWrite.erase(buffersToWrite.begin()+2, buffersToWrite.end());
            }


            for (const auto& buffer : buffersToWrite){
                if(buffer->count() < 16)
                    continue;
                stream << buffer->data();
            }
            stream.flush();
            if (m_pLogFile->pos()>=m_nMaxFileSize)
                m_bUseLogFile = CreateNewLogFile(QCoreApplication::instance());

            if (buffersToWrite.size() > 2)
            {
              // drop non-bzero-ed buffers, avoid trashing
              buffersToWrite.resize(2);
            }

            if (!newBuffer1)
            {
              assert(!buffersToWrite.empty());
              newBuffer1 = std::move(buffersToWrite.back());
              buffersToWrite.pop_back();
              newBuffer1->truncate(0);
            }

            if (!newBuffer2)
            {
              assert(!buffersToWrite.empty());
              newBuffer2 = std::move(buffersToWrite.back());
              buffersToWrite.pop_back();
              newBuffer2->truncate(0);
            }
            buffersToWrite.clear();
        }
        m_pLogFile->flush();
    }

}

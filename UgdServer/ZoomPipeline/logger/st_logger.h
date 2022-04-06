#ifndef ST_LOGGER_H
#define ST_LOGGER_H

#include "boost/thread.hpp"
#include "boost/noncopyable.hpp"
#include "boost/thread/lock_factories.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <memory>
#include <vector>
#include <QDateTime>
#include <QDir>
#include <QByteArray>
#include <QMutex>
#include <QCoreApplication>


class ZPMainFrame;
namespace STMsgLogger{
    class st_logger : public boost::noncopyable
    {
	public:
        explicit st_logger();
        void setZPMainFrame(ZPMainFrame *ui);
		void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
        void MessageAppend(const QString &msg);
		int maxFileSize() const;
		int logLevel() const;
        void start();
        void stop();
        void setMaxFileSize(int nSize);
        void setLogLevel(int);
	protected:
		bool CreateNewLogFile(QCoreApplication * app);
		QFile * m_pLogFile;
		bool m_bUseLogFile;
		QString m_currLogFileName;
		int m_nLogLevel;
        int m_nMaxFileSize;

    private:
        void run();



    private:
        static const int S_BUFFER_SIZE = 4000*1024;
        ZPMainFrame *m_zpMainFrame;
        typedef std::unique_ptr<QByteArray> BufferPtr;
        typedef std::vector<BufferPtr> BufferVector;
        BufferPtr m_currentBuffer;
        BufferPtr m_nextBuffer;
        std::vector<BufferPtr> m_buffers;
        boost::mutex m_logMutex;
        boost::condition_variable_any m_logCondi;
        std::unique_ptr<boost::thread> m_logThread;
        bool m_isRunning;
	};
}
#endif // ST_LOGGER_H

﻿#include "databaseresource.h"
#include <QThread>
#include <QMutexLocker>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
namespace ZPDatabase{


	DatabaseResource::DatabaseResource(QObject *parent) :
		QThread(parent)
	{
		bTerm = false;
	}
	//When a QThread finished, the database for this thread should be removed.
    void DatabaseResource::on_finishedThread()
	{
		QMutexLocker locker(&m_mutex_reg);
		QThread * pThread = qobject_cast<QThread *>( sender());
		//Get The quiting thread
		if (pThread && m_ThreadOwnedMainDBs.contains(pThread) )
		{
			QMap<QString, QDateTime> mainNames = m_ThreadOwnedMainDBs[pThread];
			//Remove every thread-owned db names for this thread.
			foreach (QString mainName, mainNames.keys())
			{
				QString threadName = QString("%1_%2").arg(mainName).arg((quint64)pThread);
				QSqlDatabase db = QSqlDatabase::database(threadName);
				if (db.isOpen()==true)
					db.close();
				QSqlDatabase::removeDatabase(threadName);
                QString msg = "Database:"+tr(" Connection removed ")+threadName+ tr(" .");
                qDebug() << msg;
				//Remove the key map
				m_ThreadsDB[mainName].remove(threadName);
			}
			//Completly remove this thread's ThreadOwnedMainDBs
			m_ThreadOwnedMainDBs.remove(pThread);

		}
	}

	/**
	 * @brief Get an database connection belong to current thread.
	 * if database does not exist, it will be added using dbtype
	 * @fn DatabaseResource::databse
	 * @param strDBName the database name
	 * @return QSqlDatabase return the database object
	 */
	QSqlDatabase  DatabaseResource::databse(QString  strDBName,bool checkConn)
	{
        QMutexLocker locker(&m_mutex_reg);
		if (false==QSqlDatabase::contains(strDBName))
		{
            QString msg =  "Database:"+tr(" Connection name ")+strDBName+ tr(" does not exist.");
            qDebug() << msg;
			return QSqlDatabase();
		}
		//We need a thread owner db , instead of the main DB template
		QThread * pThread = currentThread();
		//We will clean the thread's db connections when thread quits.
		if (pThread)
            connect (pThread,&QThread::finished,this,&DatabaseResource::on_finishedThread,Qt::UniqueConnection);
		//Make a process-unique db id
        QString threadName = QString("%1_%2").arg(strDBName).arg((quint64)currentThread());

		if (false==QSqlDatabase::contains(threadName))
		{
            //QSqlDatabase db = QSqlDatabase::cloneDatabase(QSqlDatabase::database(strDBName),threadName);
            QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", threadName);
            if(m_dbNames.contains(strDBName))
            {
                tagConnectionPara para = m_dbNames[strDBName];
                db.setHostName(para.HostAddr);
                db.setPort(para.port);
                db.setDatabaseName(para.dbName);
                db.setUserName(para.User);
                db.setPassword(para.Pass);
            }
			if (db.open()==false)
			{
				QString msg =  "Database:"+tr(" Connection name ")+threadName+
						tr(" Can not be cloned from database %1.").arg(strDBName)+
                        tr(" Err String:") + db.lastError().text();
                qDebug() << msg;
                return QSqlDatabase();
			}
			else
			{
				QString msg =  "Database:"+tr(" Connection name ")+threadName+
						tr(" has been cloned from database %1.").arg(strDBName);

                qDebug() << msg;
			}
			m_ThreadsDB[strDBName].insert(threadName);
            m_ThreadOwnedMainDBs[pThread][strDBName] = QDateTime::currentDateTime();
        }
		//Confirm the thread-owned db is still open
        QSqlDatabase db = QSqlDatabase::database(threadName);


        bool bNeedReconnect = false;
		if (db.isOpen()==true)
        {
			QDateTime dtmLatsAct = m_ThreadOwnedMainDBs[pThread][strDBName];
			if (dtmLatsAct.addSecs(5) < QDateTime::currentDateTime())
                checkConn = true;
            if(dtmLatsAct.addSecs(120) > QDateTime::currentDateTime())
            {
                tagConnectionPara & para = m_dbNames[strDBName];
                if (checkConn==true && para.testSQL.length())
                {
                    QSqlQuery query(db);
                    query.prepare(para.testSQL);
                    query.exec(para.testSQL);
                    if (query.exec() != true && query.lastError().type() != QSqlError::NoError)
                    {
                        QString msg = "Database:"+tr(" Connection  ")+threadName+ tr(" Need re-connect. MSG=");
                        msg += query.lastError().text();
                        qDebug() << msg;
                        bNeedReconnect = true;
                    }
                    else
                        m_ThreadOwnedMainDBs[pThread][strDBName] = QDateTime::currentDateTime();
                }
            }
            else
            {
                QString msg = "Database:"+tr(" Connection  ")+threadName+ tr(" Need re-connect. idel timeout");
                qWarning()<<msg;
                bNeedReconnect = true;
            }

			if (bNeedReconnect==true)
			{
				db.close();
				QSqlDatabase::removeDatabase(threadName);
				m_ThreadsDB[strDBName].remove(threadName);
				m_ThreadOwnedMainDBs[pThread].remove(strDBName);
			}
		}
		else
		{
			QSqlDatabase::removeDatabase(threadName);
			m_ThreadsDB[strDBName].remove(threadName);
			m_ThreadOwnedMainDBs[pThread].remove(strDBName);
			bNeedReconnect = true;
        }

		if (bNeedReconnect==true)
		{
            //db = QSqlDatabase::cloneDatabase(QSqlDatabase::database(strDBName),threadName);
            db = QSqlDatabase::addDatabase("QMYSQL", threadName);
            if(m_dbNames.contains(strDBName))
            {
                tagConnectionPara para = m_dbNames[strDBName];
                db.setHostName(para.HostAddr);
                db.setPort(para.port);
                db.setDatabaseName(para.dbName);
                db.setUserName(para.User);
                db.setPassword(para.Pass);
            }

			if (db.open()==true)
			{
				QString msg = "Database:"+tr(" Connection  ")+threadName+ tr(" Re-Established.");
                qDebug() << msg;
				m_ThreadsDB[strDBName].insert(threadName);
                m_ThreadOwnedMainDBs[pThread][strDBName] = QDateTime::currentDateTime();
			}
			else
			{
				QString msg =  "Database:"+tr(" Connection name ")+threadName+
						tr(" Can not be cloned from database %1.").arg(strDBName)+
						tr(" Err String:") + db.lastError().text();
                qDebug() << msg;
				m_ThreadsDB[strDBName].remove(threadName);
				m_ThreadOwnedMainDBs[pThread].remove(strDBName);
                return QSqlDatabase();

			}
        }
        return  db;
	}
	void DatabaseResource::remove_connections()
	{
		QMap<QString,tagConnectionPara> sets;
		{
			QMutexLocker locker(&m_mutex_reg);
			sets = currentDatabaseConnections();
		}
		foreach (QString name, sets.keys())
		{
			this->remove_connection(name);
		}
	}

	//!Remove Database
	void DatabaseResource::remove_connection(QString  strDBName)
	{
		QMutexLocker locker(&m_mutex_reg);
		if (true==QSqlDatabase::contains(strDBName))
		{
			QSqlDatabase db = QSqlDatabase::database(strDBName);
			if (db.isOpen()==true)
				db.close();
			QSqlDatabase::removeDatabase(strDBName);
			QString msg = "Database:"+tr(" Connection removed ")+strDBName+ tr(" .");
            qDebug() << msg;
			RemoveTreadsConnections(strDBName);
			m_ThreadsDB[strDBName].clear();
		}
		else
		{
            QString msg = "Database:"+tr(" Connection name ")+strDBName+ tr(" does not exist.");
            qDebug() << msg;
		}
		m_dbNames.remove(strDBName) ;

	}
	void DatabaseResource::RemoveTreadsConnections(QString mainName)
	{
		if (m_ThreadsDB.contains(mainName))
		{
			QSet<QString> & sethreadNames = m_ThreadsDB[mainName];
			foreach(QString str, sethreadNames)
			{
				QSqlDatabase db = QSqlDatabase::database(str);
				if (db.isOpen()==true)
					db.close();
				QSqlDatabase::removeDatabase(str);
                QString msg = "Database:"+tr(" Connection removed ")+str+ tr(" .");
                qDebug() << msg;
			}
			//Remove thread map.
			foreach (QThread * ptr, m_ThreadOwnedMainDBs.keys())
			{
				QMap<QString, QDateTime> & threadOwnedMainDB = m_ThreadOwnedMainDBs[ptr];
				threadOwnedMainDB.remove(mainName);
			}
		}
	}

	/**
	 * @brief add a database connection resource
	 *
	 * @fn DatabaseResource::addConnection
	 * @param connName the user-specified name standing for this connection
	 * @param type the Qt-Sql database driver name, QPSQL, QMYSQL, etc.
	 * @param HostAddr the host address will connect to.
	 * @param port the port will connect to.
	 * @param dbName the database schema name
	 * @param User username
	 * @param Pass password
	 * @param ExtraOptions some extra options.
	 * @param testSQL if this para is not empty, confirmConnection will call this SQL to confirm the db is OK,
	 * for example, select 1+1 , will return 2 if db is ok.
	 * @return bool succeed : true
	 */
	bool DatabaseResource::addConnection(
			QString  connName,
			QString  type,
			QString  HostAddr,
			int port,
			QString  dbName,
			QString  User,
			QString  Pass,
			QString  ExtraOptions,
			QString  testSQL
			)
	{
		QMutexLocker locker(&m_mutex_reg);
		tagConnectionPara para;
		para.connName = connName;
		para.type = type;
		para.HostAddr = HostAddr;
		para.port = port;
		para.dbName = dbName;
		para.User = User;
		para.Pass = Pass;
		para.status = true;
		para.testSQL = testSQL;
		para.ExtraOptions = ExtraOptions;
        qDebug() << QString("HostAddr:%1, Port:%2, DbName:%3, User:%4, Pass:%5, testSQL:%6")
                    .arg(HostAddr).arg(port).arg(dbName).arg(User).arg(Pass).arg(testSQL) << type;

		if (true==QSqlDatabase::contains(connName))
		{
			QSqlDatabase db = QSqlDatabase::database(connName);
			if (db.isOpen()==true)
				db.close();
			QSqlDatabase::removeDatabase(connName);
            QString msg = "Database:"+tr(" Connection removed ")+connName+ tr(" .");
            qDebug() << msg;
		}

		m_dbNames[connName] = para;
        QSqlDatabase db = QSqlDatabase::addDatabase(type, connName);
		db.setHostName(HostAddr);
		db.setPort(port);
		db.setDatabaseName(dbName);
		db.setUserName(User);
		db.setPassword(Pass);
        db.setConnectOptions("MYSQL_OPT_RECONNECT=1");
		if (db.open()==true)
		{
            QString msg ="Database:"+ tr(" Connection  ")+connName+ tr(" Established.");
            qDebug() << msg;
			return true;
		}
        QString msg = "Database:"+tr(" Connection  ")+connName+ tr(" Can't be opened. MSG=");
		msg += db.lastError().text();
        qDebug() << msg;
//		QSqlDatabase::removeDatabase(connName);
//		m_dbNames.remove(connName) ;
		return false;
	}
	/**
	 * @brief this method runs in a special guarding thread
	 * to confirm the connection resource is still OK
	 * see  DatabaseResource::run()
	 * @fn DatabaseResource::confirmConnection
	 * @param connName the connection name which to be tested.
	 * @return bool the check result.
	 */
	bool DatabaseResource::confirmConnection (QString  connName)
	{
		QMutexLocker locker(&m_mutex_reg);
		if (false==m_dbNames.contains(connName))
		{
			QString msg = "Database:"+tr(" Connection ")+connName+ tr(" has not been added.");
            qDebug() << msg;
			return false;
		}
        tagConnectionPara & para = m_dbNames[connName];
		if (true==QSqlDatabase::contains(connName)  )
        {
            QSqlDatabase db = QSqlDatabase::database(connName);
			if (db.isOpen()==true)
			{
				bool bNeedDisconnect = false;
				if (para.testSQL.length())
				{
					QSqlQuery query(db);
					query.exec(para.testSQL);
					if (query.lastError().type()!=QSqlError::NoError)
					{
						QString msg = "Database:"+tr(" Connection  ")+connName+ tr(" confirm failed. MSG=");
                        msg += query.lastError().text();
                        qDebug() << msg;
						bNeedDisconnect = true;
					}
				}
				if (bNeedDisconnect==true)
				{
					db.close();
					QSqlDatabase::removeDatabase(connName);
					return false;
				}
				else
					return true;
            }
            QString msg = "Database:"+tr(" Connection ")+connName+ tr(" has not been opened.");
            qDebug() << msg;
			db = QSqlDatabase::addDatabase(para.type,para.connName);
			db.setHostName(para.HostAddr);
			db.setPort(para.port);
			db.setDatabaseName(para.dbName);
			db.setUserName(para.User);
			db.setPassword(para.Pass);
			db.setConnectOptions(para.ExtraOptions);
			if (db.open()==true)
			{
				para.status = true;
				para.lastError = "";
                msg = "Database:"+tr(" Connection  ")+connName+ tr(" Re-Established.");
                qDebug() << msg;
				return true;
			}
			QSqlDatabase::removeDatabase(connName);
			msg ="Database:"+ tr(" Connection  ")+connName+ tr(" Can't be opened. MSG=");
            msg += db.lastError().text();
            qDebug() << msg;
			para.status = false;
			para.lastError = db.lastError().text();
			return false;
		}

		QSqlDatabase db = QSqlDatabase::addDatabase(para.type,para.connName);
		db.setHostName(para.HostAddr);
		db.setPort(para.port);
		db.setDatabaseName(para.dbName);
		db.setUserName(para.User);
		db.setPassword(para.Pass);
		db.setConnectOptions(para.ExtraOptions);
		if (db.open()==true)
		{
			para.status = true;
			para.lastError = "";
			QString msg ="Database:"+ tr(" Connection  ")+connName+ tr(" Re-Established.");
            qDebug() << msg;
			return true;
		}
		QString msg ="Database:"+ tr(" Connection  ")+connName+ tr(" Can't be opened. MSG=");
        msg += db.lastError().text();
        qDebug() << msg;
		QSqlDatabase::removeDatabase(connName);
		para.status = false;
		para.lastError = db.lastError().text();
		return false;
	}

	void DatabaseResource::run()
	{
		while(bTerm==false)
		{
			QMap<QString,tagConnectionPara> sets;
			{
				QMutexLocker locker(&m_mutex_reg);
				sets = currentDatabaseConnections();
			}

			foreach (QString name, sets.keys())
			{
                confirmConnection(name) ;
				if (bTerm==true)
					break;
			}
			if (bTerm==false)
				QThread::currentThread()->msleep(30000);
		}

	}

};

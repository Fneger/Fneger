#include <QApplication>
#include "st_logger.h"
#include "zpmainframe.h"
#include <QSharedMemory>
#include <QMessageBox>

STMsgLogger::st_logger g_logger;

void stMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    g_logger.MessageOutput(type,context,msg);
}

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    QApplication a(argc, argv);
    //qInstallMessageHandler(stMessageOutput);
    g_logger.start();
    QSharedMemory shared("ugd_server_share");				//?????????
    if (shared.attach())						//????????????????????????????
    {
        QMessageBox::warning(NULL, QObject::tr("Warning"), QObject::tr("Program is running!"));
        return 0;
    }
    shared.create(1);
    a.setApplicationName("MdvrUgdServer");

//    Install message handler

    ZPMainFrame zpServer;
    zpServer.setWindowTitle(a.applicationName());
    g_logger.setLogLevel(3);
    g_logger.setZPMainFrame(&zpServer);
    zpServer.setLogger(&g_logger);
    zpServer.startStop();
    zpServer.show();

    int ret = a.exec();
    google::protobuf::ShutdownProtobufLibrary();
    return ret;
}

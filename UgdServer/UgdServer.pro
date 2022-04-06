QT       += core gui network sql

unix:QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = UgdServer
TEMPLATE = app
RC_ICONS = UgdServer.ico

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += USE_DATABASE
DEFINES += QT_NO_SSL
DEFINES += USE_PROTOBUF

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ZoomPipeline/asio/casiodatabase.cpp \
        ZoomPipeline/asio/casiolisten.cpp \
        ZoomPipeline/asio/casiotcpserver.cpp \
        ZoomPipeline/asio/casiotcpsocket.cpp \
        ZoomPipeline/asio/csocketsession.cpp \
        ZoomPipeline/asio/ctcpabstractsocket.cpp \
        ZoomPipeline/cluster/zp_clusternode.cpp \
        ZoomPipeline/cluster/zp_clusterterm.cpp \
        ZoomPipeline/database/databaseresource.cpp \
        ZoomPipeline/database/databasetool.cpp \
        ZoomPipeline/logger/st_logger.cpp \
        ZoomPipeline/network/zp_net_threadpool.cpp \
        ZoomPipeline/network/zp_netlistenthread.cpp \
        ZoomPipeline/network/zp_nettransthread.cpp \
        ZoomPipeline/network/zp_tcpclient.cpp \
        ZoomPipeline/network/zp_tcpserver.cpp \
        ZoomPipeline/pipeline/zp_pipeline.cpp \
        ZoomPipeline/pipeline/zp_pltaskbase.cpp \
        ZoomPipeline/pipeline/zp_plworkingthread.cpp \
        ZoomPipeline/protobuf/cbuffer.cpp \
        ZoomPipeline/protobuf/cclientnode.cpp \
        ZoomPipeline/protobuf/ccodec.cpp \
        ZoomPipeline/protobuf/protobuf_message.pb.cc \
        ZoomPipeline/smartlink/st_client_event.cpp \
        ZoomPipeline/smartlink/st_client_file.cpp \
        ZoomPipeline/smartlink/st_client_protocol.cpp \
        ZoomPipeline/smartlink/st_client_table.cpp \
        ZoomPipeline/smartlink/st_clientnode_applayer.cpp \
        ZoomPipeline/smartlink/st_clientnode_basetrans.cpp \
        ZoomPipeline/smartlink/st_global_def.cpp \
        ZoomPipeline/smartlink/st_message.cpp \
        ZoomPipeline/smartlink/st_packet_tool.cpp \
        cgarbagecollector.cpp \
        dialogaddressinput.cpp \
        main.cpp \
        zpmainframe.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ZoomPipeline/asio/casiodatabase.h \
    ZoomPipeline/asio/casiolisten.h \
    ZoomPipeline/asio/casiotcpserver.h \
    ZoomPipeline/asio/casiotcpsocket.h \
    ZoomPipeline/asio/csocketsession.h \
    ZoomPipeline/asio/ctcpabstractsocket.h \
    ZoomPipeline/asio/ioserviceclass.h \
    ZoomPipeline/cluster/cross_svr_messages.h \
    ZoomPipeline/cluster/zp_clusternode.h \
    ZoomPipeline/cluster/zp_clusterterm.h \
    ZoomPipeline/database/databaseresource.h \
    ZoomPipeline/database/databasetool.h \
    ZoomPipeline/logger/st_logger.h \
    ZoomPipeline/network/ssl_config.h \
    ZoomPipeline/network/zp_net_threadpool.h \
    ZoomPipeline/network/zp_netlistenthread.h \
    ZoomPipeline/network/zp_nettransthread.h \
    ZoomPipeline/network/zp_tcpclient.h \
    ZoomPipeline/network/zp_tcpserver.h \
    ZoomPipeline/pipeline/zp_pipeline.h \
    ZoomPipeline/pipeline/zp_pltaskbase.h \
    ZoomPipeline/pipeline/zp_plworkingthread.h \
    ZoomPipeline/protobuf/Callbacks.h \
    ZoomPipeline/protobuf/Endian.h \
    ZoomPipeline/protobuf/cbuffer.h \
    ZoomPipeline/protobuf/cclientnode.h \
    ZoomPipeline/protobuf/ccodec.h \
    ZoomPipeline/protobuf/dispatcher.h \
    ZoomPipeline/protobuf/dispatcher_lite.h \
    ZoomPipeline/protobuf/google-inl.h \
    ZoomPipeline/protobuf/protobuf_message.pb.h \
    ZoomPipeline/smartlink/st_client_event.h \
    ZoomPipeline/smartlink/st_client_file.h \
    ZoomPipeline/smartlink/st_client_protocol.h \
    ZoomPipeline/smartlink/st_client_table.h \
    ZoomPipeline/smartlink/st_clientnode_applayer.h \
    ZoomPipeline/smartlink/st_clientnode_basetrans.h \
    ZoomPipeline/smartlink/st_global_def.h \
    ZoomPipeline/smartlink/st_message.h \
    ZoomPipeline/smartlink/st_packet_tool.h \
    cgarbagecollector.h \
    dialogaddressinput.h \
    zlib/include/zconf.h \
    zlib/include/zlib.h \
    zpmainframe.h

INCLUDEPATH += $$PWD/../boost_1_77_0


FORMS += \
    dialogaddressinput.ui \
    zpmainframe.ui

RESOURCES += \
    resource.qrc

INCLUDEPATH += ZoomPipeline/asio




INCLUDEPATH += D:/boost/v141/include
DEPENDPATH += D:/boost/v141/include
INCLUDEPATH += asio

win32:CONFIG(release, debug|release): LIBS += -LD:/boost/v141/lib/ -llibboost_thread-vc141-mt-x64-1_77
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/boost/v141/lib/ -llibboost_thread-vc141-mt-gd-x64-1_77

DEFINES += PROTOBUF_USE_DLLS
LIBS += -LC:/protobuf/bin/ -LC:/protobuf/lib/ -llibprotobuf

INCLUDEPATH += C:/protobuf/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/zlib/lib/ -lzlibstatic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/zlib/lib/ -lzlibstaticd

INCLUDEPATH += $$PWD/zlib/include
DEPENDPATH += $$PWD/zlib/include

INCLUDEPATH += \
    ZoomPipeline/cluster \
    ZoomPipeline/database \
    ZoomPipeline/logger \
    ZoomPipeline/network \
    ZoomPipeline/pipeline \
    ZoomPipeline/smartlink \
    ZoomPipeline/protobuf


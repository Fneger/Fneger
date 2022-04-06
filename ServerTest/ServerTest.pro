QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += USE_PROTOBUF

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../UgdServer/ZoomPipeline/asio/casiolisten.cpp \
        ../UgdServer/ZoomPipeline/asio/casiotcpclient.cpp \
        ../UgdServer/ZoomPipeline/asio/casiotcpserver.cpp \
        ../UgdServer/ZoomPipeline/asio/casiotcpsocket.cpp \
        ../UgdServer/ZoomPipeline/asio/csocketsession.cpp \
        ../UgdServer/ZoomPipeline/asio/ctcpabstractsocket.cpp \
        ../UgdServer/ZoomPipeline/protobuf/cbuffer.cpp \
        ../UgdServer/ZoomPipeline/protobuf/ccodec.cpp \
        ../UgdServer/ZoomPipeline/protobuf/protobuf_message.pb.cc \
        ctestthread.cpp \
        main.cpp \
        zp_tcpserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../boost_1_77_0
INCLUDEPATH += ../UgdServer/ZoomPipeline/asio
INCLUDEPATH += ../UgdServer/ZoomPipeline/protobuf

HEADERS += \
    ../UgdServer/ZoomPipeline/asio/casiolisten.h \
    ../UgdServer/ZoomPipeline/asio/casiotcpclient.h \
    ../UgdServer/ZoomPipeline/asio/casiotcpserver.h \
    ../UgdServer/ZoomPipeline/asio/casiotcpsocket.h \
    ../UgdServer/ZoomPipeline/asio/csocketsession.h \
    ../UgdServer/ZoomPipeline/asio/ctcpabstractsocket.h \
    ../UgdServer/ZoomPipeline/asio/ioserviceclass.h \
    ../UgdServer/ZoomPipeline/protobuf/Endian.h \
    ../UgdServer/ZoomPipeline/protobuf/cbuffer.h \
    ../UgdServer/ZoomPipeline/protobuf/ccodec.h \
    ../UgdServer/ZoomPipeline/protobuf/dispatcher.h \
    ../UgdServer/ZoomPipeline/protobuf/dispatcher_lite.h \
    ../UgdServer/ZoomPipeline/protobuf/google-inl.h \
    ../UgdServer/ZoomPipeline/protobuf/protobuf_message.pb.h \
    ctestthread.h \
    zp_tcpserver.h

win32:CONFIG(release, debug|release): LIBS += -LD:/boost/v141/lib/ -llibboost_thread-vc141-mt-x64-1_77
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/boost/v141/lib/ -llibboost_thread-vc141-mt-gd-x64-1_77

DEFINES += PROTOBUF_USE_DLLS
LIBS += -LC:/protobuf/bin/ -LC:/protobuf/lib/ -llibprotobuf

INCLUDEPATH += C:/protobuf/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../UgdServer/zlib/lib/ -lzlibstatic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../UgdServer/zlib/lib/ -lzlibstaticd

INCLUDEPATH += $$PWD/../UgdServer/zlib/include
DEPENDPATH += $$PWD/../UgdServer/zlib/include

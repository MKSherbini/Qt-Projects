QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Control/controltabcontroller.cpp \
    Control/setuptabcontroller.cpp \
    Model/instrument.cpp \
    Model/instsocket.cpp \
    Model/provider.cpp \
    Model/settings.cpp \
    View/aboutbox.cpp \
    View/controltab.cpp \
    View/setuptab.cpp \
    main.cpp \
    View/mainwindow.cpp \
    startup.cpp \
    utils.cpp

HEADERS += \
    Control/controltabcontroller.h \
    Control/setuptabcontroller.h \
    Model/instrument.h \
    Model/instsocket.h \
    Model/provider.h \
    Model/settings.h \
    View/aboutbox.h \
    View/controltab.h \
    View/mainwindow.h \
    View/setuptab.h \
    startup.h \
    utils.h

FORMS += \
    View/aboutbox.ui \
    View/controltab.ui \
    View/mainwindow.ui \
    View/setuptab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    VfpResources.qrc

DISTFILES += \
    settings.json

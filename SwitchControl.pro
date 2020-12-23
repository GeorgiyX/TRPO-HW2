QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/faqpage.cpp \
    src/loginpage.cpp \
    src/main.cpp \
    src/switchcontrol.cpp \
    src/switchdatamapper.cpp \
    src/tweakpage.cpp

HEADERS += \
    src/businesslogic.h \
    src/faqpage.h \
    src/loginpage.h \
    src/switchcontrol.h \
    src/switchdatamapper.h \
    src/tweakpage.h

FORMS += \
    ui/loginpage.ui \
    ui/faqpage.ui \
    ui/switchcontrol.ui \
    ui/tweakpage.ui

QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

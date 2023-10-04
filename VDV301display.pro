#-------------------------------------------------
#
# Project created by QtCreator 2018-06-07T13:35:40
#
#-------------------------------------------------

QT += core gui
QT += xml
QT += core gui network
QT += httpserver
QT += svg
#CONFIG   += console



#DEFINES+= QZEROCONF_STATIC

#include(qtzeroconf/qtzeroconf.pri)


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets

TARGET = VDV301display
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES+= QZEROCONF_STATIC
include(VDV301subscriber/QtZeroConf/qtzeroconf.pri)

target.path=/home/pi
target.files=VDV301displayNew
INSTALLS+=target

SOURCES += \
    VDV301publisher/colordisplayrules.cpp \
    VDV301publisher/customerinformationservice.cpp \
    VDV301publisher/devicemanagementservice.cpp\
    VDV301publisher/httpsluzba.cpp \
    VDV301publisher/httpserverpublisher.cpp \
    VDV301publisher/subscriber.cpp \
    VDV301publisher/ticketvalidationservice.cpp \
    VDV301publisher/xmlcommon.cpp \
    VDV301publisher/xmlcustomerinformationservice.cpp \
    VDV301publisher/xmldevicemanagementservice.cpp \
    VDV301publisher/xmlticketvalidationservice.cpp \
    VDV301struktury/line.cpp \
    VDV301subscriber/cissubscriber.cpp \
    VDV301subscriber/devmgmtpublisherstruct.cpp \
    VDV301subscriber/devmgmtsubscriber.cpp \
    VDV301subscriber/httpserversubscriber.cpp \
    VDV301subscriber/ibisipsubscriber.cpp \
    inlineformatparser.cpp \
    VDV301subscriber/ibisipsubscriberonepublisher.cpp \
    labelvykreslovani.cpp \
        main.cpp \
        mainwindow.cpp \
    pasmovedvojicelcd.cpp \
    svgrenderer.cpp \
    xmlparser.cpp \
    VDV301struktury/cestaudaje.cpp \
    VDV301struktury/obeh.cpp \
    VDV301struktury/pasmo.cpp \
    VDV301struktury/prestup.cpp \
    VDV301struktury/prestupmpv.cpp \
    VDV301struktury/spoj.cpp \
    VDV301struktury/zastavka.cpp \
    VDV301struktury/zastavkacil.cpp \
    VDV301struktury/specialnihlaseni.cpp \
    barvylinek.cpp

HEADERS += \
    VDV301publisher/colordisplayrules.h \
    VDV301publisher/customerinformationservice.h \
    VDV301publisher/devicemanagementservice.h \
    VDV301publisher/httpsluzba.h \
    VDV301publisher/httpserverpublisher.h \
    VDV301publisher/subscriber.h \
    VDV301publisher/ticketvalidationservice.h \
    VDV301publisher/xmlcommon.h \
    VDV301publisher/xmlcustomerinformationservice.h \
    VDV301publisher/xmldevicemanagementservice.h \
    VDV301publisher/xmlticketvalidationservice.h \
    VDV301struktury/line.h \
    VDV301subscriber/cissubscriber.h \
    VDV301subscriber/devmgmtpublisherstruct.h \
    VDV301subscriber/devmgmtsubscriber.h \
    VDV301subscriber/httpserversubscriber.h \
    VDV301subscriber/ibisipsubscriber.h \
    VDV301subscriber/ibisipsubscriberonepublisher.h \
    inlineformatparser.h \
    labelvykreslovani.h \
    mainwindow.h \
    pasmovedvojicelcd.h \
    svgrenderer.h \
    xmlparser.h \
    VDV301struktury/cestaudaje.h \
    VDV301struktury/obeh.h \
    VDV301struktury/prestup.h \
    VDV301struktury/pasmo.h \
    VDV301struktury/prestupmpv.h \
    VDV301struktury/specialnihlaseni.h \
    VDV301struktury/spoj.h \
    VDV301struktury/zastavka.h \
    VDV301struktury/zastavkacil.h \
    barvylinek.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

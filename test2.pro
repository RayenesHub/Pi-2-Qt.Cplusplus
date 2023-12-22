QT +=  core gui sql serialport network multimedia multimediawidgets charts printsupport widgets axcontainer serialport
QT +=sql
//arduino
QT += printsupport
QT += serialport
//stat
QT += core gui charts
QT       += core gui sql
QT += printsupport
QT += widgets multimedia
QT += serialport
QT += charts
QT += axcontainer
//qr
CONFIG += enable_encoder_qr_code
include(QZXing/QZXing.pri)


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
    EMPLOYES.cpp \
    ExcelExportHelper.cpp \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    employes_p.cpp \
    espaces.cpp \
    event.cpp \
    fornisseur_p.cpp \
    fournisseur.cpp \
    main.cpp \
    mainwindow.cpp \
    smtp.cpp \
    stat_combo.cpp

HEADERS += \
    EMPLOYES.h \
    ExcelExportHelper.h \
    arduino.h \
    client.h \
    connection.h \
    employes_p.h \
    espaces.h \
    event.h \
    fornisseur_p.h \
    fournisseur.h \
    mainwindow.h \
    popup.h \
    smtp.h \
    stat_combo.h

FORMS += \
    employes_p.ui \
    fornisseur_p.ui \
    mainwindow.ui \
    stat_combo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

QT       += core gui sql network

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
    adminwidget.cpp \
    control.cpp \
    domain_detail.cpp \
    line.cpp \
    login.cpp \
    main.cpp \
    no_frame_widget.cpp \
    person_widget.cpp \
    pick.cpp \
    purchase.cpp \
    register_widget.cpp \
    widget.cpp

HEADERS += \
    adminwidget.h \
    control.h \
    domain_detail.h \
    line.h \
    login.h \
    no_frame_widget.h \
    person_widget.h \
    pick.h \
    purchase.h \
    register_widget.h \
    server.h \
    superbutton.h \
    widget.h

FORMS += \
    adminwidget.ui \
    control.ui \
    domain_detail.ui \
    login.ui \
    no_frame_widget.ui \
    person_widget.ui \
    pick.ui \
    purchase.ui \
    register_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    SRC.qrc

RC_ICONS=emoji.ico

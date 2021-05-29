QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbuttondepartment.cpp \
    addbuttonemployee.cpp \
    companymodel.cpp \
    companymodelxmlparser.cpp \
    companywidget.cpp \
    departmentheaderwidget.cpp \
    departmentwidget.cpp \
    employeewidget.cpp \
    employeewidgeteditor.cpp \
    main.cpp \
    mainwindow.cpp \
    undoredosystem.cpp

HEADERS += \
    addbuttondepartment.h \
    addbuttonemployee.h \
    companymodel.h \
    companymodelxmlparser.h \
    companywidget.h \
    departmentheaderwidget.h \
    departmentwidget.h \
    employeewidget.h \
    employeewidgeteditor.h \
    mainwindow.h \
    undoredosystem.h

FORMS += \
    addbuttondepartment.ui \
    addbuttonemployee.ui \
    departmentheaderwidget.ui \
    employeewidget.ui \
    employeewidgeteditor.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

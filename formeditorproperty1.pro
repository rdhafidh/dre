#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T16:35:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG +=  BUILD_GRAPHICSVIEW silent
TARGET = dre
TEMPLATE = app
CONFIG +=console  
INCLUDEPATH += baseview items delegates delegates/propertyeditor
 
VERSION= 0.1.2  
QMAKE_TARGET_COMPANY = "Ridwan Abdul Hafidh (ridwanabdulhafidh@gmail.com)"
QMAKE_TARGET_DESCRIPTION = "A database report editor"
QMAKE_TARGET_COPYRIGHT = "Ridwan Abdul Hafidh @ 2018"
QMAKE_TARGET_PRODUCT = "Crossplatform OS"
RC_ICONS =  rect815.png.ico
RC_LANG = "en-US"


include(itemShapeBases\itemshapeinclude.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    baseview/baseview.cpp \
    baseview/sceneview.cpp \
    items/textitem.cpp \
    items/baseallitems.cpp items/selectionmarkerhandlebase.cpp \
    items/customobyek.cpp \
    items/imageitem.cpp \
    items/pageitem.cpp \
    delegates/propertyedititemdelegate.cpp \
    delegates/propertyeditor/utiljsonstringproperty.cpp \
    delegates/propertyeditor/imagefilesetpropertyeditor.cpp \ 
    manystructuiobjectparam.cpp \
    baseview/undocommand.cpp \
    formdesign.cpp \
    tabwidgetutama.cpp \
    items/ruleritem.cpp

HEADERS  += mainwindow.h \
    tabwidgetutama.h \
    baseview/baseview.h \
    baseview/sceneview.h \
    items/textitem.h\
    items/baseallitems.h items/selectionmarkerhandlebase.h \
    items/customobyek.h \
    items/imageitem.h \
    items/pageitem.h \
     delegates/propertyedititemdelegate.h  delegates/propertyeditor/utiljsonstringproperty.h \
    delegates/propertyeditor/imagefilesetpropertyeditor.h \
    manystructuiobjectparam.h \
    baseview/undocommand.h \
    formdesign.h \
    items/ruleritem.h

FORMS    += mainwindow.ui \
    delegates/propertyeditor/imagefilesetpropertyeditor.ui \
    formdesign.ui

RESOURCES += \
    ikons.qrc

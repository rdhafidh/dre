CONFIG+= console silent
TEMPLATE = app 
QT += network gui
include(../tools_build.pri)
include(../flatsrc.pri)
include(../thirdparty/zint-2.6.1/backend_qt/backend_qt.pro)


TARGET = busywaitserver
SOURCES += main.cc

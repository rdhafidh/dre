 
set(ITEM_SRC
    baseallitems.cpp 
    customobyek.cpp
    ellipseitem.cpp
    handlerpointerruler.cpp
    imageitem.cpp
    itemshapebase.cpp
    lineitem.cpp
    pageitem.cpp
    rectangleitem.cpp
    ruleritem.cpp
    selectionlineitemhandler.cpp
    selectionmarkerhandlebase.cpp
    textitem.cpp
    triangleitem.cpp
    constvalue.h
    baseallitems.h 
    customobyek.h
    ellipseitem.h
    handlerpointerruler.h
    imageitem.h
    itemshapebase.h
    lineitem.h
    pageitem.h
    rectangleitem.h
    ruleritem.h
    selectionlineitemhandler.h
    selectionmarkerhandlebase.h
    textitem.h
    triangleitem.h
    )   
 
include_directories ( ../../app/baseview ../../app )
add_library(items STATIC ${ITEM_SRC})

target_compile_features(items PUBLIC cxx_std_11)
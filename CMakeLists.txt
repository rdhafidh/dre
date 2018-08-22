cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(dre)  
 

find_package(Qt5 COMPONENTS Core Gui Widgets Network PrintSupport Sql  REQUIRED)
include_directories (${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#add specific target 
add_subdirectory(lib/items)
add_subdirectory(thirdparty)
add_subdirectory(app)
add_subdirectory(tools)

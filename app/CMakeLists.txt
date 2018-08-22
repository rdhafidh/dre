 
set(SRCS 
	formdesign.cpp
	main.cpp
	mainwindow.cpp 
	manystructuiobjectparam.cpp 
	tabwidgetutama.cpp
	baseview/baseview.cpp 
	baseview/baseview.h 
	baseview/sceneview.cpp 
	baseview/sceneview.h 
	baseview/undocommand.cpp 
	baseview/undocommand.h 
        delegates/propertyedititemdelegate.cpp 
        delegates/propertyedititemdelegate.h
        delegates/propertyeditor/imagefilesetpropertyeditor.cpp 
        delegates/propertyeditor/imagefilesetpropertyeditor.h 
        delegates/propertyeditor/utiljsonstringproperty.cpp 
        delegates/propertyeditor/utiljsonstringproperty.h
	dre_resource.rc 
	res.qrc
	) 
    
include_directories (../lib/items delegates delegates/propertyeditor baseview ../lib )

add_executable(dre ${SRCS} )

target_compile_features(dre PUBLIC cxx_std_11)
target_link_libraries(dre  Qt5::Core Qt5::Widgets Qt5::Gui Qt5::PrintSupport  zint flatbuffers items)
	
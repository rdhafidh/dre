
set(tool_src
	main.cpp
	serverhandler.cpp 
	)
 
add_executable(busywait ${tool_src} )
target_link_libraries(busywait Qt5::Core Qt5::Gui Qt5::Network flatbuffers zint items)

	
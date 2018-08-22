
if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

include_directories( 
			${CMAKE_CURRENT_SOURCE_DIR}/include 
			${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers
			)

set(FLATSRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/code_generators.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idl_parser.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/idl_gen_text.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflection.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/code_generators.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/flatbuffers.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/hash.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/idl.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/util.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/reflection.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/reflection_generated.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/stl_emulation.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/flexbuffers.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/registry.h
   ${CMAKE_CURRENT_SOURCE_DIR}/include/flatbuffers/minireflect.h
  )
 
add_library(flatbuffers STATIC ${FLATSRCS})


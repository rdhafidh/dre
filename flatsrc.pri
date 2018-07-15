
FLATDIR = $$PWD/thirdparty/flatbuffers
SOURCES += $${FLATDIR}/src/code_generators.cpp \
  $${FLATDIR}/src/idl_parser.cpp \
  $${FLATDIR}/src/idl_gen_text.cpp \
  $${FLATDIR}/src/reflection.cpp \
  $${FLATDIR}/src/util.cpp
  
INCLUDEPATH += $${FLATDIR}/include $${FLATDIR}/include/flatbuffers

HEADERS += $${FLATDIR}/include/flatbuffers/code_generators.h
  $${FLATDIR}/include/flatbuffers/base.h
  $${FLATDIR}/include/flatbuffers/flatbuffers.h
  $${FLATDIR}/include/flatbuffers/hash.h
  $${FLATDIR}/include/flatbuffers/idl.h
  $${FLATDIR}/include/flatbuffers/util.h
  $${FLATDIR}/include/flatbuffers/reflection.h
  $${FLATDIR}/include/flatbuffers/reflection_generated.h
  $${FLATDIR}/include/flatbuffers/stl_emulation.h
  $${FLATDIR}/include/flatbuffers/flexbuffers.h
  $${FLATDIR}/include/flatbuffers/registry.h
  $${FLATDIR}/include/flatbuffers/minireflect.h

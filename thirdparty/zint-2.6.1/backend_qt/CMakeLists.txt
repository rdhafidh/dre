
if(MSVC)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS )
endif() 
add_compile_definitions(NO_PNG)

set(ZINT_SRCS 
		   ${CMAKE_CURRENT_SOURCE_DIR}/../backend/2of5.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/auspost.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/aztec.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/bmp.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/codablock.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code1.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code128.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code16k.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code49.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/common.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/composite.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/dllversion.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/dmatrix.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/dotcode.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/eci.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/emf.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/gif.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/gridmtx.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/gs1.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/hanxin.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/imail.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/large.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/library.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/maxicode.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/medical.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/pcx.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/pdf417.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/plessey.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/png.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/postal.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/ps.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/qr.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/raster.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/reedsol.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/render.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/rss.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/svg.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/telepen.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/tif.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/../backend/upcean.c 
           ${CMAKE_CURRENT_SOURCE_DIR}/qzint.cpp 
		   ${CMAKE_CURRENT_SOURCE_DIR}/../backend/aztec.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/bmp.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/code49.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/common.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/composite.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/dmatrix.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/eci.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/font.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/gridmtx.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/gs1.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/hanxin.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/large.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/maxicode.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/pcx.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/pdf417.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/reedsol.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/rss.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/sjis.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/stdint_msvc.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/../backend/zint.h 
            ${CMAKE_CURRENT_SOURCE_DIR}/qzint.h 
		   )
		   
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../backend  ${CMAKE_CURRENT_SOURCE_DIR})
		   
add_library(zint STATIC ${ZINT_SRCS})

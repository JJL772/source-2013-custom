project(lzmalib C)

set(SRCS C/Alloc.c
        C/LzFind.c
        C/LzmaDec.c
        C/LzmaEnc.c
        C/LzmaLib.c)

add_definitions(-D_7ZIP_ST)

add_library(lzmalib STATIC ${SRCS})
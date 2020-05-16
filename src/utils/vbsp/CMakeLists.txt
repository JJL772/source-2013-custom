#
#
# Project script for vbsp
#
#
project(vbsp C CXX)

# Platform specific sources
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

set(SRCS	${PUBLIC_INCLUDE}/collisionutils.cpp
            ${PUBLIC_INCLUDE}/disp_common.cpp
            ${PUBLIC_INCLUDE}/disp_powerinfo.cpp
            ${PUBLIC_INCLUDE}/loadcmdline.cpp
            ${PUBLIC_INCLUDE}/lumpfiles.cpp
            ../common/mstristrip.cpp
            ../common/physdll.cpp
            ../common/scratchpad_helpers.cpp
            ${PUBLIC_INCLUDE}/scratchpad3d.cpp
            ../common/utilmatlib.cpp
            ${PUBLIC_INCLUDE}/zip_utils.cpp
            ${PUBLIC_INCLUDE}/builddisp.cpp
            ${PUBLIC_INCLUDE}/chunkfile.cpp
            ${PUBLIC_INCLUDE}/filesystem_helpers.cpp
            ${PUBLIC_INCLUDE}/filesystem_init.cpp
            ../common/bsplib.cpp
            ../common/cmdlib.cpp
            ../common/filesystem_tools.cpp
            ../common/map_shared.cpp
            ../common/pacifier.cpp
            ../common/polylib.cpp
            ../common/scriplib.cpp
            ../common/threads.cpp
            ../common/tools_minidump.cpp
            ${PUBLIC_INCLUDE}/scratchpad3d.cpp)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ *.c *.cpp)
list(APPEND SRCS ${SOURCES})

# Preprocessor defs
set(DEFINES			-DMACRO_MATHLIB -DPROTECTED_THINGS_DISABLE)

# Platform-specific preprocessor defines
set(WIN32_DEFINES	)
set(POSIX32_DEFINES	)
set(WIN64_DEFINES	)
set(POSIX64_DEFINES	)
set(WINDOWS_DEFINES	)
set(POSIX_DEFINES	)

set(PLATFORM_64BIT_DEFINES	)
set(PLATFORM_32BIT_DEFINES 	)

# Links dirs to search for link libs in
set(LINK_DIRS	)
set(WINDOWS_LINK_DIRS	)
set(POSIX_LINK_DIRS		)
set(WIN32_LINK_DIRS		)
set(WIN64_LINK_DIRS		)
set(POSIX32_LINK_DIRS	)
set(POSIX64_LINK_DIRS	)

# Generic libs to link against
set(LINK_LIBS			tier1 tier0 vstdlib)

# Other projects this one depends on
set(DEPENDENCIES		)

# Platform specific link libs
#set(WINDOWS_LINK_LIBS	bitmap fgdlib mathlib tier2 vtf tier1 tier0 vstdlib ws2_32 odbc32 odbccp32 winmm)
set(WIN32_LINK_LIBS		)
set(WIN64_LINK_LIBS		)
#set(POSIX_LINK_LIBS     bitmap fgdlib mathlib tier2 vtf tier1 tier0 vstdlib c m rt pthread)
set(POSIX32_LINK_LIBS	)
set(POSIX64_LINK_LIBS	)

# Generic include dirs
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/ ../common/)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET vbsp)

# Set the output file name
set(OUTPUT_FILE_NAME vbsp)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/exe-base.cmake)

# Other static libs we need
set(WINDOWS_LINK_LIBS bitmap fgdlib mathlib tier2 vtf tier1 tier0 vstdlib ws2_32 odbc32 odbccp32 winmm)

set(POSIX_LINK_LIBS
        ${LIBPUBLIC}/vtf.a
        ${LIBPUBLIC}/bitmap.a
        fgdlib
        ${LIBPUBLIC}/tier2.a
        lzmalib
        mathlib
        tier1
        ${LIBPUBLIC}/libz.a
        tier0
        vstdlib
        m
        c
        dl
        rt
        pthread
        )

if(DEFINED WINDOWS)
    target_link_libraries(vbsp ${WINDOWS_LINK_LIBS})
endif(DEFINED WINDOWS)

if(DEFINED POSIX)
    target_link_libraries(vbsp ${POSIX_LINK_LIBS})
endif(DEFINED POSIX)

install(TARGETS vbsp
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)

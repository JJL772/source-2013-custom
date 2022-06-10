#
#
# Project script for vbsp
#
#
project(vvis C CXX)

# Platform specific sources
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

set(SRCS
        flow.cpp
        vvis.cpp
        WaterDist.cpp
        ../common/bsplib.cpp
        ../common/cmdlib.cpp
        ../common/pacifier.cpp
        ../common/scratchpad_helpers.cpp
        ../common/scriplib.cpp
        ../common/threads.cpp
        ../common/tools_minidump.cpp
        ${PUBLIC_INCLUDE}/collisionutils.cpp
        ${PUBLIC_INCLUDE}/filesystem_helpers.cpp
        ${PUBLIC_INCLUDE}/loadcmdline.cpp
        ${PUBLIC_INCLUDE}/lumpfiles.cpp
        ${PUBLIC_INCLUDE}/scratchpad3d.cpp
        ${PUBLIC_INCLUDE}/zip_utils.cpp
        ${PUBLIC_INCLUDE}/filesystem_init.cpp
        ../common/filesystem_tools.cpp
        )

# Preprocessor defs
set(DEFINES			-DVVIS -DPROTECTED_THINGS_DISABLE)

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
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/ ../common/ ../vmpi)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET vvis)

# Set the output file name
set(OUTPUT_FILE_NAME vvis)

set(SHARED_LIB 1)
set(STATIC_LIBR 0)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/library-base.cmake)

# Other static libs we need
set(WINDOWS_LINK_LIBS bitmap mathlib tier2 vtf tier1 tier0 vstdlib ws2_32 odbc32 odbccp32 winmm)

set(POSIX_LINK_LIBS
        ${LIBPUBLIC}/vtf.a
        ${LIBPUBLIC}/bitmap.a
        ${LIBPUBLIC}/tier2.a
        mathlib
        tier1
        tier0
        vstdlib
        m
        c
        dl
        rt
        pthread
        )

if(DEFINED WINDOWS)
    target_link_libraries(vvis ${WINDOWS_LINK_LIBS})
endif(DEFINED WINDOWS)

if(DEFINED POSIX)
    target_link_libraries(vvis ${POSIX_LINK_LIBS})
endif(DEFINED POSIX)

install(TARGETS vvis
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)

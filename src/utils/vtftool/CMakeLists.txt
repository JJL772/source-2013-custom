#
#
# Project script for vbsp
#
#
project(vtftool C CXX)

# Platform specific sources
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

set(SRCS	)

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
set(WIN32_LINK_LIBS		)
set(WIN64_LINK_LIBS		)
set(POSIX32_LINK_LIBS	)
set(POSIX64_LINK_LIBS	)

# Generic include dirs
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/ ${ROOT}/thirdparty)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET vtftool)

# Set the output file name
set(OUTPUT_FILE_NAME vtftool)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/exe-base.cmake)

# Other static libs we need
set(WINDOWS_LINK_LIBS vtf bitmap mathlib tier2 tier1 tier0 vstdlib)

set(POSIX_LINK_LIBS
        ${LIBPUBLIC}/vtf.a
        ${LIBPUBLIC}/bitmap.a
        mathlib
        ${LIBPUBLIC}/tier2.a
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
    target_link_libraries(vtftool ${WINDOWS_LINK_LIBS})
endif(DEFINED WINDOWS)

if(DEFINED POSIX)
    target_link_libraries(vtftool ${POSIX_LINK_LIBS})
endif(DEFINED POSIX)

install(TARGETS vtftool
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)

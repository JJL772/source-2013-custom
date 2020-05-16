#
#
# Project script for vbsp
#
#
project(vrad C CXX)

# Platform specific sources
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

set(SRCS
        ${PUBLIC_INCLUDE}/bsptreedata.cpp
        ${PUBLIC_INCLUDE}/disp_common.cpp
        ${PUBLIC_INCLUDE}/disp_powerinfo.cpp
        ${PUBLIC_INCLUDE}/loadcmdline.cpp
        ${PUBLIC_INCLUDE}/lumpfiles.cpp
        ${PUBLIC_INCLUDE}/zip_utils.cpp
        ${PUBLIC_INCLUDE}/builddisp.cpp
        ${PUBLIC_INCLUDE}/chunkfile.cpp
        ${PUBLIC_INCLUDE}/dispcoll_common.cpp
        #../common/mpi_stats.cpp
        #../common/MySqlDatabase.cpp
        ../common/pacifier.cpp
        ../common/physdll.cpp
        ../common/utilmatlib.cpp
        #../common/vmpi_tools_shared.cpp
        ../common/bsplib.cpp
        ../common/cmdlib.cpp
        ../common/map_shared.cpp
        ../common/polylib.cpp
        ../common/scriplib.cpp
        ../common/threads.cpp
        ../common/tools_minidump.cpp
        ../common/filesystem_tools.cpp
        ${PUBLIC_INCLUDE}/collisionutils.cpp
        ${PUBLIC_INCLUDE}/filesystem_helpers.cpp
        ${PUBLIC_INCLUDE}/filesystem_init.cpp
        ${PUBLIC_INCLUDE}/scratchpad3d.cpp
        ${PUBLIC_INCLUDE}/ScratchPadUtils.cpp
        disp_vrad.cpp
        imagepacker.cpp
        incremental.cpp
        leaf_ambient_lighting.cpp
        lightmap.cpp
        macro_texture.cpp
        origface.cpp
        radial.cpp
        samplehash.cpp
        trace.cpp
        vismat.cpp
        vrad.cpp
        vrad_dispcoll.cpp
        vraddetailprops.cpp
        vraddisps.cpp
        vraddll.cpp
        vradstaticprops.cpp)

# Preprocessor defs
set(DEFINES			-DVRAD -DPROTECTED_THINGS_DISABLE)

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
set(TARGET vrad)

# Set the output file name
set(OUTPUT_FILE_NAME vrad)

set(SHARED_LIB 1)
set(STATIC_LIBR 0)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/library-base.cmake)

# Other static libs we need
set(WINDOWS_LINK_LIBS bitmap fgdlib mathlib tier2 raytrace vtf tier1 tier0 vstdlib ws2_32 odbc32 odbccp32 winmm)

set(POSIX_LINK_LIBS
        ${LIBPUBLIC}/vtf.a
        ${LIBPUBLIC}/bitmap.a
        fgdlib
        ${LIBPUBLIC}/tier2.a
        lzmalib
        raytrace
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
    target_link_libraries(vrad ${WINDOWS_LINK_LIBS})
endif(DEFINED WINDOWS)

if(DEFINED POSIX)
    target_link_libraries(vrad ${POSIX_LINK_LIBS})
endif(DEFINED POSIX)

install(TARGETS vrad
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION bin)

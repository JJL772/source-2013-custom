project(studiomdl C CXX)

set(SRCS
	#"bmpread.cpp"
		"collisionmodel.cpp"
		"hardwarematrixstate.cpp"
		"hardwarevertexcache.cpp"
		"matsys.cpp"
		"mrmsupport.cpp"
		"objsupport.cpp"
		"optimize.cpp"
		"perfstats.cpp"
		"simplify.cpp"
		"studiomdl.cpp"
		"tristrip.cpp"
		"unifylods.cpp"
		"v1support.cpp"
		"write.cpp")

# Preprocessor defs
set(DEFINES	-DSTUDIOMDL=1)

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
set(LINK_LIBRARIES 		)

# Platform specific link libs
set(WIN32_LINK_LIBS		)
set(WIN64_LINK_LIBS		)
set(POSIX32_LINK_LIBS	)
set(POSIX64_LINK_LIBS	)

# Generic include dirs
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/tier1 ${PUBLIC_INCLUDE}/tier0)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET studiomdl)

# Set the output file name
set(OUTPUT_FILE_NAME studiomdl)

# If this is a shared lib
#set(SHARED_LIB 0)

# If this is a static lib
#set(STATIC_LIB 1)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/exe-base.cmake)

target_link_libraries(studiomdl tier0 tier1)

if(POSIX)
    target_link_libraries(studiomdl dl m rt c)
endif(POSIX)

target_include_directories(
	studiomdl PUBLIC

	"${CMAKE_CURRENT_LIST_DIR}/../common"
)

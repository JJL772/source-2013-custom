#
#
# Source base with CMake
#
#
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

if(DEFINED POSIX OR CLANG_BUILD)
	if(NOT BUILD_64BIT)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags" FORCE)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags" FORCE)
		set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS} -m32")
	endif(NOT BUILD_64BIT)
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -march=i686 -msse3 -g")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math -march=i686 -msse3 -g")
endif()

if(DEFINED UNIX_CROSS AND NOT USE_MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-attributes -Wno-write-strings ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes -Wno-write-strings -Wno-conversion-null")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffast-math")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")

	# Clean up the prefixes
	set(CMAKE_STATIC_LIBRARY_PREFIX "")
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
	set(CMAKE_IMPORT_LIBRARY_PREFIX "")
endif(DEFINED UNIX_CROSS AND NOT USE_MSVC)

# TODO: Make this work for windows
if(USE_SSE)
	if((DEFINED UNIX_CROSS OR DEFINED POSIX OR DEFINED CLANG_BUILD) AND NOT USE_MSVC)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse3")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")
	endif((DEFINED UNIX_CROSS OR DEFINED POSIX OR DEFINED CLANG_BUILD) AND NOT USE_MSVC)
endif(USE_SSE)

if(USE_AVX)
	if((DEFINED UNIX_CROSS OR DEFINED POSIX OR DEFINED CLANG_BUILD) AND NOT USE_MSVC)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
	endif((DEFINED UNIX_CROSS OR DEFINED POSIX OR DEFINED CLANG_BUILD) AND NOT USE_MSVC)
endif(USE_AVX)

if(DEFINED POSIX OR UNIX_CROSS AND NOT USE_MSVC)
	# NO undefined in shared libs
	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")
	
	#set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wno-invalid-offsetof -Wno-enum-compare -Wno-format-security -Wno-multichar -Wno-ignored-attributes")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing -fabi-compat-version=2")
	endif()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-narrowing -Wno-enum-compare -Wno-format-security -Wno-multichar")
	if(DEFINED POSIX64)
		set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS} -l:ld-linux-x86_64.so.2")
		set(CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/")
	else()
		set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS} -l:ld-linux.so.2")
		set(CMAKE_LIBRARY_PATH "/usr/lib/i386-linux-gnu/ /usr/lib32")
	endif(DEFINED POSIX64)
endif()
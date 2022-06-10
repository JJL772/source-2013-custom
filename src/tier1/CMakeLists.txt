#
#
# Project script for Tier1
#
#
project(tier1 C CXX)

# Platform specific sources 
set(WINDOWS_SRCS			"processor_detect.cpp")
set(POSIX_SRCS			"qsort_s.cpp"		
						"processor_detect_linux.cpp"
						"pathmatch.cpp")

set(SRCS	
		"bitbuf.cpp"
		"newbitbuf.cpp"
		"byteswap.cpp"
		"characterset.cpp"
		"checksum_crc.cpp"
		"checksum_md5.cpp"
		"checksum_sha1.cpp"
		"commandbuffer.cpp"
		"convar.cpp"
		"datamanager.cpp"
		"diff.cpp"
		"generichash.cpp"
		"ilocalize.cpp"
		"interface.cpp"
		"KeyValues.cpp"
		"kvpacker.cpp"
		"lzmaDecoder.cpp"
		#"lzss.cpp" [!$SOURCESDK]
		"mempool.cpp"
		"memstack.cpp"
		"NetAdr.cpp"
		"splitstring.cpp"
		"rangecheckedvar.cpp"
		"reliabletimer.cpp"
		"stringpool.cpp"
		"strtools.cpp"
		"strtools_unicode.cpp"
		"tier1.cpp"
		"tokenreader.cpp"
		"sparsematrix.cpp"
		"uniqueid.cpp"
		"utlbuffer.cpp"
		"utlbufferutil.cpp"
		"utlstring.cpp"
		"utlsymbol.cpp"
		"utlbinaryblock.cpp"
		"snappy.cpp"
		"snappy-sinksource.cpp"
		"snappy-stubs-internal.cpp"
		"${ROOT}/utils/lzma/C/LzmaDec.c")
		
if(UNIX AND NOT UNIX_CROSS)
	list(APPEND SRCS "math_proxy.cpp")
endif(UNIX AND NOT UNIX_CROSS)


# Preprocessor defs
set(DEFINES	-DTIER1_STATIC_LIB=1)

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
set(TARGET tier1)

# Set the output file name
set(OUTPUT_FILE_NAME tier1)

# If this is a shared lib
set(SHARED_LIB 0)

# If this is a static lib
set(STATIC_LIB 1)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/library-base.cmake)

target_link_libraries(tier1 tier0)
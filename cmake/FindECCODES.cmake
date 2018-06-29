
option(USE_OPENJP "Using OpenJpeg" ON)

if(USE_OPENJP)
	find_library(OPENJP_LIBRARY
		NAMES openjp2
		PATHS ${OPENJP_INSTALL_PREFIX}
		PATH_SUFFIXES lib
		NO_DEFAULT_PATH
	)
	if(OPENJP_LIBRARY)
		set(OPENJP_FOUND TRUE)
		message(STATUS "Found OpenJPEG: ${OPENJP_LIBRARY}")
	endif()
endif()


if(ECCODES_INSTALL_PREFIX)
    set(ECCODES_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
    set(ECCODES_LIBRARY_HINTS ${ECCODES_INSTALL_PREFIX}/lib)
endif()


find_path(
	ECCODES_INCLUDE_DIR 
	NAMES eccodes.h
    PATHS ${ECCODES_INSTALL_PREFIX} ${ECCODES_INCLUDE_DIR} /usr/include /usr/local/include 
	PATH_SUFFIXES include
    NO_DEFAULT_PATH
)


if(WIN32 AND (NOT CYGWIN))
	find_file(
        ECCODES_LIBRARY
		NAMES grib_api_lib.lib
        PATHS ${ECCODES_INSTALL_PREFIX} ${ECCODES_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
else()
	find_library(
        ECCODES_LIBRARY 
		NAMES eccodes
        PATHS ${ECCODES_INSTALL_PREFIX} ${ECCODES_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
endif()

if(ECCODES_INCLUDE_DIR AND ECCODES_LIBRARY)
    set(ECCODES_FOUND TRUE)
endif()


if(NOT OPENJP_FOUND)
    if(ECCODES_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find openjpeg library")
    endif()
endif()

message("ECCODES_INCLUDE_DIR ${ECCODES_INCLUDE_DIR}")
message("ECCODES_LIBRARY ${ECCODES_LIBRARY}")

if(ECCODES_FOUND)
	set(ECCODES_LIBRARIES 
		${OPENJP_LIBRARY}
		${ECCODES_LIBRARY}
	)
    if(NOT ECCODES_FIND_QUIETLY)
        message(STATUS "Found ecCodes: ${ECCODES_LIBRARY}")
    endif()
else()
    if(ECCODES_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find ecCodes library")
    endif()
endif()
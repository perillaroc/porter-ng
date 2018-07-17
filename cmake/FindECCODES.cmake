
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
    set(EcCodes_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
    set(EcCodes_LIBRARY_HINTS ${ECCODES_INSTALL_PREFIX}/lib)
endif()


find_path(
	EcCodes_INCLUDE_DIR 
	NAMES eccodes.h
    PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_INCLUDE_DIR} /usr/include /usr/local/include 
	PATH_SUFFIXES include
    NO_DEFAULT_PATH
)


if(WIN32 AND (NOT CYGWIN))
	find_file(
        EcCodes_LIBRARY
		NAMES grib_api_lib.lib
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
else()
	find_library(
        EcCodes_LIBRARY 
		NAMES eccodes
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
endif()

#message("EcCodes_INCLUDE_DIR ${EcCodes_INCLUDE_DIR}")
#message("EcCodes_LIBRARY ${EcCodes_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EcCodes
	REQUIRED_VARS EcCodes_INCLUDE_DIR EcCodes_LIBRARY
)

if(NOT OPENJP_FOUND)
    if(EcCodes_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find openjpeg library")
    endif()
endif()

if(EcCodes_FOUND AND NOT TARGET EcCodes::EcCodes)
	add_library(EcCodes::EcCodes UNKNOWN IMPORTED)
	set_target_properties(EcCodes::EcCodes PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		IMPORTED_LOCATION "${EcCodes_LIBRARY}"
		INTERFACE_LINK_LIBRARIES "${OPENJP_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${EcCodes_INCLUDE_DIR}"		
	)
	mark_as_advanced(
		EcCodes_INCLUDE_DIR
		EcCodes_LIBRARY
	)
endif()
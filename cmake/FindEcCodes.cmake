if(WIN32 AND (NOT CYGWIN))
    option(USE_OPENJP "Using OpenJpeg" ON)

    if(USE_OPENJP)
		find_package(OpenJPEG CONFIG REQUIRED)
    endif()


    if(ECCODES_INSTALL_PREFIX)
        set(EcCodes_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
        set(EcCodes_LIBRARY_HINTS ${ECCODES_INSTALL_PREFIX}/lib)
    endif()

    find_path(
        EcCodes_INCLUDE_DIR
        NAMES eccodes.h
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_INCLUDE_DIR}
        PATH_SUFFIXES include
        NO_DEFAULT_PATH
    )

	find_file(
        EcCodes_LIBRARY
		NAMES grib_api_libd.lib
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
else()
    find_package(eccodes CONFIG REQUIRED)
#    message("ECCODES_INCLUDE_DIRS ${ECCODES_INCLUDE_DIRS}")
#    message("ECCODES_TPL_LIBRARIES ${ECCODES_TPL_LIBRARIES}")
#    message("ECCODES_SELF_INCLUDE_DIRS ${ECCODES_SELF_INCLUDE_DIRS}")

    set(EcCodes_INCLUDE_DIR ${ECCODES_INCLUDE_DIRS})
    set(EcCodes_LINK_LIBRARIES ${ECCODES_TPL_LIBRARIES})

	find_library(
        EcCodes_LIBRARY
		NAMES eccodes
        PATHS "${ECCODES_SELF_INCLUDE_DIRS}/.."
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EcCodes
	REQUIRED_VARS EcCodes_INCLUDE_DIR EcCodes_LIBRARY
)

if(EcCodes_FOUND AND NOT TARGET EcCodes::EcCodes)

	add_library(EcCodes::EcCodes UNKNOWN IMPORTED)
	set_target_properties(EcCodes::EcCodes PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		IMPORTED_LOCATION "${EcCodes_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${EcCodes_INCLUDE_DIR}")


    if(WIN32 AND (NOT CYGWIN))
        set_target_properties(EcCodes::EcCodes PROPERTIES
            INTERFACE_LINK_LIBRARIES "${OPENJP_LIBRARY}")

		target_link_libraries(EcCodes::EcCodes INTERFACE openjp2)

    else()
        set_target_properties(EcCodes::EcCodes PROPERTIES
            INTERFACE_LINK_LIBRARIES "${EcCodes_LINK_LIBRARIES}")
    endif()

	mark_as_advanced(
		EcCodes_INCLUDE_DIR
		EcCodes_LIBRARY
	)
endif()
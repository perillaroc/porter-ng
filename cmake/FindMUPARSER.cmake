if(MUPARSER_INSTALL_PREFIX)
    set(MuParser_INCLUDE_HINTS ${MUPARSER_INSTALL_PREFIX}/include)
    set(MuParser_LIBRARY_HINTS ${MUPARSER_INSTALL_PREFIX}/lib)
endif()

find_path(
        MuParser_INCLUDE_DIR
		NAMES muParser.h
        PATHS /usr/include /usr/local/include ${MUPARSER_INSTALL_PREFIX} ${MuParser_INCLUDE_DIR}
		PATH_SUFFIXES include
        NO_DEFAULT_PATH
)

find_library(
        MuParser_LIBRARY
        NAMES muparser
        PATHS /usr/lib  /usr/local/lib ${MuParser_LIBRARY_HINTS} ${MuParser_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

#message("MuParser_INCLUDE_DIR ${MuParser_INCLUDE_DIR}")
#message("MuParser_LIBRARY ${MuParser_LIBRARY}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MuParser
	REQUIRED_VARS MuParser_INCLUDE_DIR MuParser_LIBRARY
)

if(MuParser_FOUND AND NOT TARGET MuParser::MuParser)
	add_library(MuParser::MuParser UNKNOWN IMPORTED)
	set_target_properties(MuParser::MuParser PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		IMPORTED_LOCATION "${MuParser_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${MuParser_INCLUDE_DIR}"
	)
	mark_as_advanced(
		MuParser_INCLUDE_DIR
		MuParser_LIBRARY
	)
endif()
#    if(NOT MuParser_FIND_QUIETLY)
#        message(STATUS "Found muParser: ${MuParser_LIBRARY}")
#    endif()
#else()
#    if(MuParser_FIND_REQUIRED)
#        MESSAGE(FATAL_ERROR "Could not find muParser library")
#    endif()
#endif()
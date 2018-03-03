if(MUPARSER_INSTALL_PREFIX)
    set(MUPARSER_INCLUDE_HINTS ${MUPARSER_INSTALL_PREFIX}/include)
    set(MUPARSER_LIBRARY_HINTS ${MUPARSER_INSTALL_PREFIX}/lib)
endif()

find_path(
        MUPARSER_INCLUDE_DIR muParser.h
        HINTS /usr/include /usr/local/include ${MUPARSER_INCLUDE_HINTS}
        NO_DEFAULT_PATH
)

find_library(
        MUPARSER_LIBRARY
        muparser
        /usr/lib  /usr/local/lib ${MUPARSER_LIBRARY_HINTS} ${MUPARSER_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if(MUPARSER_INCLUDE_DIR AND MUPARSER_LIBRARY)
    set(MUPARSER_FOUND TRUE)
endif()

if(MUPARSER_FOUND)
    if(NOT MUPARSER_FIND_QUIETLY)
        message(STATUS "Found muParser: ${MUPARSER_LIBRARY}")
    endif()
else()
    if(MUPARSER_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find muParser library")
    endif()
endif()
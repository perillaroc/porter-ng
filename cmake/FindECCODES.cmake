
if(ECCODES_INSTALL_PREFIX)
    set(ECCODES_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
    set(ECCODES_LIBRARY_HINTS ${ECCODES_INSTALL_PREFIX}/lib)
endif()

find_path(
        ECCODES_INCLUDE_DIR eccodes.h
        HINTS /usr/include /usr/local/include ${ECCODES_INCLUDE_HINTS}
        NO_DEFAULT_PATH
)

find_library(
        ECCODES_LIBRARY
        eccodes
        /usr/lib  /usr/local/lib ${ECCODES_LIBRARY_HINTS} ${ECCODES_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if(ECCODES_INCLUDE_DIR AND ECCODES_LIBRARY)
    set(ECCODES_FOUND TRUE)
endif()

if(ECCODES_FOUND)
    if(NOT ECCODES_FIND_QUIETLY)
        message(STATUS "Found ecCodes: ${ECCODES_LIBRARY}")
    endif()
else()
    if(ECCODES_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find ecCodes library")
    endif()
endif()
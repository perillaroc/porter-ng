cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_STANDARD 11)

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

set(PORTER_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_BINARY_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_to_grib/src
        )

add_subdirectory(src)
add_subdirectory(example)
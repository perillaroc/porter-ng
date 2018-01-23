cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_STANDARD 11)

find_path(
        ECCODES_INCLUDE_DIR eccodes.h
        HINTS /usr/include /usr/local/include
        NO_DEFAULT_PATH
)

find_library(
        ECCODES_LIBRARY
        eccodes
        /usr/lib  /usr/local/lib ${ECCODES_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

add_subdirectory(src)
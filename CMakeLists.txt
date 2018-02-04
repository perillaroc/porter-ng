cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(ECCODES REQUIRED)

set(PORTER_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_BINARY_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_to_grib/src
        )

add_subdirectory(src)
add_subdirectory(example)
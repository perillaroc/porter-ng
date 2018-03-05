cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(ECCODES REQUIRED)

set(PORTER_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_BINARY_DIR}/src/grads_parser/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/grads_convert/src
        )
set(PORTER_TEST_DATA_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/data)

set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

add_subdirectory(src)
add_subdirectory(example)
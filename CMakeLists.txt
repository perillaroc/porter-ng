cmake_minimum_required(VERSION 3.10.0)

project(porter_ng)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(EcCodes REQUIRED)

if(WIN32 AND NOT CYGWIN)
    set(Boost_USE_DEBUG_RUNTIME ON)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
endif()

find_package(Boost
        REQUIRED
        COMPONENTS
            system
            filesystem
            date_time
)

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
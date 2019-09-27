cmake_minimum_required(VERSION 3.12)

project(porter_ng)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# if(WIN32 AND NOT CYGWIN)
#     set(Boost_USE_DEBUG_RUNTIME ON)
#     set(Boost_USE_STATIC_LIBS ON)
#     set(Boost_USE_STATIC_RUNTIME OFF)
# endif()

find_package(Boost REQUIRED
	COMPONENTS
    system
    filesystem
    date_time
)

find_package(EcCodes REQUIRED)

set(PORTER_TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")

option(USE_OPENMP "Using OpenMP in Porter" OFF)
option(USE_THREAD "Using thread in Porter" OFF)
option(ENABLE_TESTS "Enable tests" OFF)

if(USE_OPENMP)
    set(PORTER_OPENMP ON)
    find_package(OpenMP REQUIRED)
endif()
if(USE_THREAD)
    set(PORTER_THREAD ON)
    find_package(Threads REQUIRED)
endif()

configure_file (
    "${PROJECT_SOURCE_DIR}/src/porter_config.h.in"
    "${PROJECT_BINARY_DIR}/src/porter_config.h"
)

if(ENABLE_TESTS)
	enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

add_subdirectory(src)
add_subdirectory(example)
project(grads_to_grib)


include_directories("${grads_parser_BINARY_DIR}/src")
include_directories("${grads_parser_SOURCE_DIR}/src")

# yaml-cpp library

if(YAMLCPP_INSTALL_PREFIX)
    set(YAMLCPP_INCLUDE_HINTS ${YAMLCPP_INSTALL_PREFIX}/include)
    set(YAMLCPP_LIBRARY_HINTS ${YAMLCPP_INSTALL_PREFIX}/lib)
endif()

find_path(
        YAMLCPP_INCLUDE_DIR yaml.h
        HINTS /usr/include/yaml-cpp /usr/local/include/yaml-cpp ${YAMLCPP_INCLUDE_HINTS}/yaml-cpp
        NO_DEFAULT_PATH
)

find_library(
        YAMLCPP_LIBRARY
        yaml-cpp
        /usr/lib  /usr/local/lib ${YAMLCPP_LIBRARY_HINTS} ${YAMLCPP_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if(YAMLCPP_LIBRARY)
    message(STATUS "Found yaml-cpp include: ${YAMLCPP_INCLUDE_DIR}")
    message(STATUS "Found yaml-cpp library: ${YAMLCPP_LIBRARY}")
endif()

# include dir
include_directories(${YAMLCPP_INCLUDE_DIR})

# lib
set(SOURCE_FILES
        src/convert_config.cpp
        src/grads_to_grib_converter.cpp
        )
add_library(grads_to_grib STATIC ${SOURCE_FILES})
target_link_libraries(grads_to_grib grads_parser ${YAMLCPP_LIBRARY})

# testing
if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
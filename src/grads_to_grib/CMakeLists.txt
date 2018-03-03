project(grads_to_grib)


include_directories("${grads_parser_BINARY_DIR}/src")
include_directories("${grads_parser_SOURCE_DIR}/src")

# yaml-cpp library
find_package(YAMLCPP REQUIRED)

# muParser library
find_package(MUPARSER REQUIRED)

# include dir
include_directories(${YAMLCPP_INCLUDE_DIR})
include_directories(${MUPARSER_INCLUDE_DIR})
include_directories(${ECCODES_INCLUDE_DIR})

# lib
set(SOURCE_FILES
        src/convert_config.cpp
        src/grads_to_grib_converter.cpp
        )
add_library(grads_to_grib STATIC ${SOURCE_FILES})
target_link_libraries(grads_to_grib grads_parser ${YAMLCPP_LIBRARY} ${MUPARSER_LIBRARY})

# testing
if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
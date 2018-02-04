project(porter)

find_package(Boost
        REQUIRED
        COMPONENTS
        program_options
        )


# include_directories(${ECCODES_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories("${grads_parser_BINARY_DIR}/src")
include_directories("${grads_parser_SOURCE_DIR}/src")
include_directories("${grads_to_grib_SOURCE_DIR}/src")

set(SRC_LIST src/main.cpp)

add_executable(porter ${SRC_LIST})
target_link_libraries(porter grads_parser grads_to_grib ${ECCODES_LIBRARY} ${Boost_PROGRAM_OPTIONS_LIBRARY})

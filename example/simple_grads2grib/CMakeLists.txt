project(example_simple_grads2grib)

include_directories(${ECCODES_INCLUDE_DIR})

add_executable(simple_grads2grib main.cpp)
target_link_libraries(simple_grads2grib grads_parser grads_convert ${ECCODES_LIBRARY})
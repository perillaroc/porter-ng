project(example_simple_grib2)

include_directories(${ECCODES_INCLUDE_DIR})

add_executable(simple_grib2 main.cpp)
target_link_libraries(simple_grib2 grads_parser ${ECCODES_LIBRARIES})
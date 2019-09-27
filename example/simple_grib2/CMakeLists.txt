project(example_simple_grib2)

add_executable(simple_grib2 main.cpp)
target_link_libraries(simple_grib2 
	PRIVATE
	Porter::grads_parser
	eccodes
)
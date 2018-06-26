project(example_simple_grads2grib)

include_directories(${ECCODES_INCLUDE_DIR})

add_executable(simple_grads2grib main.cpp)

target_link_libraries(simple_grads2grib PUBLIC
	$<TARGET_LINKER_FILE:grads_parser>
	$<TARGET_LINKER_FILE:grads_convert>	 
	${ECCODES_LIBRARY}
)

target_include_directories(simple_grads2grib PUBLIC
	$<TARGET_PROPERTY:grads_convert,INTERFACE_INCLUDE_DIRECTORIES>
	$<TARGET_PROPERTY:grads_parser,INTERFACE_INCLUDE_DIRECTORIES>
)
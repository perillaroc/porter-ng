project(example_simple_grads2grib)

include_directories(${ECCODES_INCLUDE_DIR})

add_executable(simple_grads2grib main.cpp)

target_link_libraries(simple_grads2grib PUBLIC 
		$<TARGET_LINKER_FILE:grads_convert>
		$<TARGET_LINKER_FILE:grads_parser>
		$<TARGET_PROPERTY:grads_convert,INTERFACE_LINK_LIBRARIES>
		$<TARGET_PROPERTY:grads_parser,INTERFACE_LINK_LIBRARIES>
		${ECCODES_LIBRARIES}
)

target_include_directories(simple_grads2grib PUBLIC
	$<TARGET_PROPERTY:grads_convert,INTERFACE_INCLUDE_DIRECTORIES>
)
project(example_simple_grads2grib)

#find_package(MuParser REQUIRED)

add_executable(simple_grads2grib main.cpp)

target_link_libraries(simple_grads2grib PUBLIC
		Porter::grads_convert
		#$<TARGET_LINKER_FILE:grads_parser>
		#$<TARGET_PROPERTY:grads_parser,INTERFACE_LINK_LIBRARIES>
		#$<$<CONFIG:Debug>:${YAMLCPP_LIBRARY_DEBUG}>
		#$<$<CONFIG:Release>:${YAMLCPP_LIBRARY_RELEASE}>
)

#target_include_directories(simple_grads2grib PUBLIC
#	$<TARGET_PROPERTY:grads_convert,INTERFACE_INCLUDE_DIRECTORIES>
#)
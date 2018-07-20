project(example_get_grads_value)

add_executable(get_grads_value main.cpp)

target_link_libraries(get_grads_value 
	Porter::grads_parser)
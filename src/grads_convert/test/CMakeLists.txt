add_executable(test_grads_convert)

target_sources(test_grads_convert
	PRIVATE
    test_main.cpp
    test_convert_config.cpp
    test_value_expression.cpp)

target_link_libraries(test_grads_convert 
	PRIVATE
    Porter::grads_convert
    GTest::gtest)

add_test(GradsToGribTest test_grads_convert)

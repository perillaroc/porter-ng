set(TEST_SRCS
    test_main.cpp
    test_convert_config.cpp
    test_value_expression.cpp)

add_executable(test_grads_convert ${TEST_SRCS})

target_link_libraries(test_grads_convert PRIVATE
    Porter::grads_convert
    GTest::gtest)

add_test(GradsToGribTest test_grads_convert)

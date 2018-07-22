set(TEST_SRCS
    test_main.cpp
    test_convert_config.cpp
    test_value_expression.cpp)

add_executable(test_grads_convert ${TEST_SRCS})

target_link_libraries(test_grads_convert PRIVATE
    Porter::grads_convert
    ${GTEST_BOTH_LIBRARIES}
    pthread)

target_include_directories(test_grads_convert PRIVATE
    ${GTEST_INCLUDE_DIRS})

add_test(GradsToGribTest test_grads_convert)

include_directories(../src)

function(grads_convert_add_test TEST_NAME TEST_EXE TEST_SOURCE_FILES)
    add_executable(${TEST_EXE} ${TEST_SOURCE_FILES} )
    target_link_libraries(${TEST_EXE} PRIVATE
            Porter::grads_convert
            ${GTEST_BOTH_LIBRARIES}
            pthread)
    add_test(${TEST_NAME} ${TEST_EXE})
endfunction()

set(TEST_SRCS
        test_main.cpp
        test_convert_config.cpp
        test_value_expression.cpp)

grads_convert_add_test(GradsToGribTest test_grads_convert "${TEST_SRCS}")

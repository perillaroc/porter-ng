include_directories(../src)

function(grads_to_grib_add_test TEST_NAME TEST_EXE TEST_SOURCE_FILES)
    add_executable(${TEST_EXE} ${TEST_SOURCE_FILES} )
    target_link_libraries(${TEST_EXE} grads_to_grib ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(${TEST_NAME} ${TEST_EXE})
endfunction()

grads_to_grib_add_test(ConvertConfigFileTest test_convert_config_file test_convert_config.cpp)

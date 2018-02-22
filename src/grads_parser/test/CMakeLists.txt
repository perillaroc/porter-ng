include_directories(../src)

set(TEST_DATA_ROOT ${PORTER_TEST_DATA_DIR})

configure_file (
        "${PROJECT_SOURCE_DIR}/test/test_config.h.in"
        "${PROJECT_BINARY_DIR}/test/test_config.h"
)
include_directories("${PROJECT_BINARY_DIR}/test")


function(porter_add_test TEST_NAME TEST_EXE TEST_SOURCE_FILES)
    add_executable(${TEST_EXE} ${TEST_SOURCE_FILES} )
    target_link_libraries(${TEST_EXE} grads_parser ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(${TEST_NAME} ${TEST_EXE})
endfunction()

porter_add_test(GradsCtlParserTest test_grads_ctl_parser test_grads_ctl_parser.cpp)
porter_add_test(GradsDataHandlerTest test_grads_data_handler test_grads_data_handler.cpp)
porter_add_test(GradsDataHandlerFullDataTest test_grads_data_handler_full_data test_grads_data_handler_full_data.cpp)
porter_add_test(GradsCtlUtilTest test_grads_ctl_util test_grads_ctl_util.cpp)

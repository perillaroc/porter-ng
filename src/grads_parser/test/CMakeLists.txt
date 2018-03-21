include_directories(../src)

set(TEST_DATA_ROOT ${PORTER_TEST_DATA_DIR})

configure_file (
        "${PROJECT_SOURCE_DIR}/test/test_config.h.in"
        "${PROJECT_BINARY_DIR}/test/test_config.h"
)
include_directories("${PROJECT_BINARY_DIR}/test")


function(grads_parser_add_test TEST_NAME TEST_EXE TEST_SOURCE_FILES)
    add_executable(${TEST_EXE} ${TEST_SOURCE_FILES} )
    target_link_libraries(${TEST_EXE} grads_parser ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(${TEST_NAME} ${TEST_EXE})
endfunction()

set(TEST_MAIN_SRCS
        test_main.cpp
        test_grads_ctl_parser.cpp
        test_grads_data_handler.cpp
        test_grads_data_handler_full_data.cpp
        test_grads_ctl_util.cpp
        )

grads_parser_add_test(GradsParserMainTest test_grads_parser_main "${TEST_MAIN_SRCS}")

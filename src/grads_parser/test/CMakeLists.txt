set(TEST_DATA_ROOT ${PORTER_TEST_DATA_DIR})

configure_file (
        "${PROJECT_SOURCE_DIR}/test/test_config.h.in"
        "${PROJECT_BINARY_DIR}/test/test_config.h"
)

set(TEST_MAIN_SRCS
    test_main.cpp
    test_grads_ctl_parser.cpp
    test_grads_data_handler.cpp
    test_grads_data_handler_full_data.cpp
    test_grads_ctl_util.cpp)

add_executable(test_grads_parser_main ${TEST_MAIN_SRCS})

target_include_directories(test_grads_parser_main PRIVATE
    ${PROJECT_BINARY_DIR}/test
    )

target_link_libraries(test_grads_parser_main PRIVATE
    Porter::grads_parser
	GTest::gtest
)

add_test(GradsParserMainTest test_grads_parser_main)

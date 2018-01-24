include_directories(../src)

add_executable(test_grads_ctl_parser test_grads_ctl_parser.cpp)

target_link_libraries(test_grads_ctl_parser grads_parser_lib gtest_main gtest pthread)

add_test(ParserTest test_grads_ctl_parser)
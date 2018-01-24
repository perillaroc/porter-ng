project(grads_parser)

find_package(Boost
        REQUIRED
        COMPONENTS system filesystem
        )

include_directories(${Boost_INCLUDE_DIRS})

# lib

set(SOURCE_FILES  src/grads_ctl.cpp src/grads_ctl_parser.cpp)
add_library(grads_parser_lib STATIC ${SOURCE_FILES})
target_link_libraries(grads_parser_lib ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

# exe
add_executable(grads_parser src/main.cpp)
target_link_libraries(grads_parser grads_parser_lib)

# testing

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(test)
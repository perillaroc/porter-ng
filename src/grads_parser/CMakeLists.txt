project(grads_parser)

find_package(Boost
        REQUIRED
        COMPONENTS
            system
            filesystem
            date_time
        )

include_directories(${Boost_INCLUDE_DIRS})

# test endian
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)

if(IS_BIG_ENDIAN)
    message("-- Found little endian")
    set(PORTER_BIG_ENDIAN 1)
    set(PORTER_LITTLE_ENDIAN 0)
else()
    message("-- Found big endian")
    set(PORTER_BIG_ENDIAN 0)
    set(PORTER_LITTLE_ENDIAN 1)
endif()

# configure file
configure_file (
        "${PROJECT_SOURCE_DIR}/src/porter_config.h.in"
        "${PROJECT_BINARY_DIR}/src/porter_config.h"
)
include_directories("${PROJECT_BINARY_DIR}/src")

# lib
set(SOURCE_FILES  src/grads_ctl.cpp src/grads_ctl_parser.cpp src/grads_data_handler.cpp src/grads_data_handler.h)
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
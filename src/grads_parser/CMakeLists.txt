project(grads_parser)

# test endian
include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)

if(IS_BIG_ENDIAN)
    message(STATUS "Set PORTER_BIG_ENDIAN")
    set(PORTER_BIG_ENDIAN 1)
    set(PORTER_LITTLE_ENDIAN 0)
else()
    message(STATUS "Set PORTER_LITTLE_ENDIAN")
    set(PORTER_BIG_ENDIAN 0)
    set(PORTER_LITTLE_ENDIAN 1)
endif()

# configure file
configure_file (
        "${PROJECT_SOURCE_DIR}/src/porter_config.h.in"
        "${PROJECT_BINARY_DIR}/src/porter_config.h"
)

# lib
set(SOURCE_FILES
        src/grads_ctl.cpp
        src/grads_ctl_parser.cpp
        src/grads_data_handler.cpp
        src/grads_message_handler.cpp
        src/grads_ctl_util.cpp
        )
add_library(grads_parser STATIC ${SOURCE_FILES})

target_include_directories(grads_parser PUBLIC
	${Boost_INCLUDE_DIRS}
	${PROJECT_BINARY_DIR}/src
)

target_link_libraries(grads_parser INTERFACE
	Boost::system
	Boost::filesystem
	Boost::date_time
	${ECCODES_LIBRARIES}
)

# testing
if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
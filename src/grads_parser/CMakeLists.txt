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

add_library(grads_parser STATIC)

target_sources(grads_parser
	PRIVATE
	src/grads_ctl.cpp
    src/grads_ctl_parser.cpp
    src/grads_data_handler.cpp
    src/grads_message_handler.cpp
    src/grads_ctl_util.cpp)

target_include_directories(grads_parser 
	PUBLIC
		${PROJECT_BINARY_DIR}/src
	INTERFACE
		${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(grads_parser 
	PUBLIC
	Boost::system
	Boost::filesystem
	Boost::date_time
)

add_library(Porter::grads_parser ALIAS grads_parser)

# testing
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
project(grads_convert)

# yaml-cpp library
find_package(yaml-cpp CONFIG REQUIRED)

# muParser library
find_package(MuParser REQUIRED)

add_library(grads_convert STATIC)

target_sources(grads_convert
	PRIVATE
	src/convert_config.cpp
	src/grads_converter.cpp
	src/value_expression.cpp)

target_link_libraries(grads_convert
	PUBLIC
		Porter::grads_parser
		eccodes
	PRIVATE
		yaml-cpp
		MuParser::MuParser
)

target_include_directories(grads_convert
	PUBLIC
		${porter_ng_BINARY_DIR}/src
	INTERFACE
		${PROJECT_SOURCE_DIR}/src
)

if(USE_OPENMP)
    target_link_libraries(grads_convert
        PUBLIC
        OpenMP::OpenMP_CXX)
endif()

if(USE_THREAD)
	target_link_libraries(grads_convert
		PUBLIC
		Threads::Threads)
endif()

add_library(Porter::grads_convert ALIAS grads_convert)

# testing
if(ENABLE_TESTS)
    add_subdirectory(test)
endif()
project(grads_convert)

# yaml-cpp library
find_package(YAMLCpp REQUIRED)

# muParser library
find_package(MuParser REQUIRED)

# lib
set(SOURCE_FILES
        src/convert_config.cpp
        src/grads_converter.cpp
        src/value_expression.cpp
        )

add_library(grads_convert STATIC 
	${SOURCE_FILES})

target_link_libraries(grads_convert 
	PUBLIC
		YAMLCpp::YAMLCpp
		MuParser::MuParser
		EcCodes::EcCodes
		Porter::grads_parser
)

target_include_directories(grads_convert 
	PUBLIC
		${porter_ng_BINARY_DIR}/src
	INTERFACE
		${PROJECT_SOURCE_DIR}/src
)

target_compile_definitions(grads_convert PRIVATE
	MUPARSER_STATIC
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
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
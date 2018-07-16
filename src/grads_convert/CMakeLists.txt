project(grads_convert)


#include_directories("${grads_parser_BINARY_DIR}/src")
#include_directories("${grads_parser_SOURCE_DIR}/src")

# yaml-cpp library
find_package(YAMLCPP REQUIRED)

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
		${ECCODES_LIBRARIES}
		Porter::grads_parser
)

target_include_directories(grads_convert 
	PUBLIC
		#$<TARGET_PROPERTY:grads_parser,INTERFACE_INCLUDE_DIRECTORIES>
		#${YAMLCPP_INCLUDE_DIR}
		${ECCODES_INCLUDE_DIR}
	INTERFACE
		${PROJECT_SOURCE_DIR}/src
)

target_compile_definitions(grads_convert PRIVATE
	MUPARSER_STATIC
)

add_library(Porter::grads_convert ALIAS grads_convert)

# testing
if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
project(grads_convert)


include_directories("${grads_parser_BINARY_DIR}/src")
include_directories("${grads_parser_SOURCE_DIR}/src")

# yaml-cpp library
find_package(YAMLCPP REQUIRED)

# muParser library
find_package(MUPARSER REQUIRED)

# lib
set(SOURCE_FILES
        src/convert_config.cpp
        src/grads_converter.cpp
        src/value_expression.cpp
        )

add_library(grads_convert STATIC 
	${SOURCE_FILES})

target_link_libraries(grads_convert 
	INTERFACE
		${YAMLCPP_LIBRARY} 
		${MUPARSER_LIBRARY}
)

target_include_directories(grads_convert PUBLIC
	$<TARGET_PROPERTY:grads_parser,INTERFACE_INCLUDE_DIRECTORIES>
	${YAMLCPP_INCLUDE_DIR}
	${MUPARSER_INCLUDE_DIR}
	${ECCODES_INCLUDE_DIR}
)

# testing
if(ENABLE_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_subdirectory(test)
endif()
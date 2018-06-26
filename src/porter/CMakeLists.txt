project(porter)

set(SRC_LIST 
	src/main.cpp
)

add_executable(porter 
	${SRC_LIST}
)

target_include_directories(porter PUBLIC
	$<TARGET_PROPERTY:grads_convert,INTERFACE_INCLUDE_DIRECTORIES>
	${VENDOR_DIR}/cxxopts/include
	${grads_parser_BINARY_DIR}/src
	${grads_parser_SOURCE_DIR}/src
	${grads_convert_SOURCE_DIR}/src
)

target_link_libraries(porter 
	PUBLIC 
		$<TARGET_LINKER_FILE:grads_convert>
		$<TARGET_LINKER_FILE:grads_parser>
		$<TARGET_PROPERTY:grads_convert,INTERFACE_LINK_LIBRARIES>
		$<TARGET_PROPERTY:grads_parser,INTERFACE_LINK_LIBRARIES>
		${ECCODES_LIBRARY}
)

install(TARGETS porter RUNTIME DESTINATION bin)
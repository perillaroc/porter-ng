project(porter)

find_package(cxxopts CONFIG REQUIRED)

add_executable(porter 
	${SRC_LIST}
)

target_sources(porter
	PRIVATE
	src/main.cpp)

target_link_libraries(porter 
	PRIVATE 
		Porter::grads_convert
		cxxopts::cxxopts
		#$<TARGET_LINKER_FILE:grads_convert>
		#$<TARGET_LINKER_FILE:grads_parser>
		#$<TARGET_PROPERTY:grads_convert,INTERFACE_LINK_LIBRARIES>
		#$<TARGET_PROPERTY:grads_parser,INTERFACE_LINK_LIBRARIES>
		#$<$<CONFIG:Debug>:${YAMLCPP_LIBRARY_DEBUG}>
		#$<$<CONFIG:Release>:${YAMLCPP_LIBRARY_RELEASE}>
)

if(USE_OPENMP)
    target_link_libraries(porter
        PUBLIC
        OpenMP::OpenMP_CXX)
endif()

install(TARGETS porter RUNTIME DESTINATION bin)
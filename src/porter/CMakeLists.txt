project(porter)

# set(Boost_USE_STATIC_LIBS ON)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("${VENDOR_DIR}/cxxopts/include")

include_directories("${grads_parser_BINARY_DIR}/src")
include_directories("${grads_parser_SOURCE_DIR}/src")
include_directories("${grads_convert_SOURCE_DIR}/src")

set(SRC_LIST src/main.cpp)

add_executable(porter ${SRC_LIST})
target_link_libraries(porter grads_parser grads_convert ${ECCODES_LIBRARY})

install(TARGETS porter RUNTIME DESTINATION bin)
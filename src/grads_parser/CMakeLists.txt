project(grads_parser)

find_package(Boost
        REQUIRED
        COMPONENTS system filesystem
        )

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp grads_ctl.cpp grads_ctl_parser.cpp)

link_libraries(${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

add_executable(grads_parser ${SOURCE_FILES})
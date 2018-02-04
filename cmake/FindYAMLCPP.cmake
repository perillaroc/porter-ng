if(YAMLCPP_INSTALL_PREFIX)
    set(YAMLCPP_INCLUDE_HINTS ${YAMLCPP_INSTALL_PREFIX}/include)
    set(YAMLCPP_LIBRARY_HINTS ${YAMLCPP_INSTALL_PREFIX}/lib)
endif()

find_path(
        YAMLCPP_INCLUDE_DIR yaml.h
        HINTS /usr/include/yaml-cpp /usr/local/include/yaml-cpp ${YAMLCPP_INCLUDE_HINTS}/yaml-cpp
        NO_DEFAULT_PATH
)

find_library(
        YAMLCPP_LIBRARY
        yaml-cpp
        /usr/lib  /usr/local/lib ${YAMLCPP_LIBRARY_HINTS} ${YAMLCPP_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

if(YAMLCPP_INCLUDE_DIR AND YAMLCPP_LIBRARY)
    set(YAMLCPP_FOUND TRUE)
endif()

if(YAMLCPP_FOUND)
    if(NOT YAMLCPP_FIND_QUIETLY)
        message(STATUS "Found yaml-cpp: ${YAMLCPP_LIBRARY}")
    endif()
else()
    if(YAMLCPP_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find yaml-cpp library")
    endif()
endif()
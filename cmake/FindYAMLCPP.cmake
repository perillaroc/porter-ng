if(YAMLCPP_INSTALL_PREFIX)
    set(YAMLCPP_INCLUDE_HINTS ${YAMLCPP_INSTALL_PREFIX}/include)
    set(YAMLCPP_LIBRARY_HINTS ${YAMLCPP_INSTALL_PREFIX}/lib)
endif()

find_path(
        YAMLCPP_INCLUDE_DIR 
		NAMES yaml-cpp/yaml.h
        PATHS /usr/include /usr/local/include ${YAMLCPP_INSTALL_PREFIX}/include
        NO_DEFAULT_PATH
)

find_library(
        YAMLCPP_LIBRARY_DEBUG
        NAMES yaml-cppd libyaml-cppmdd
        PATHS /usr/lib  /usr/local/lib ${YAMLCPP_INSTALL_PREFIX}/lib ${YAMLCPP_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

find_library(
        YAMLCPP_LIBRARY_RELEASE
        NAMES yaml-cpp libyaml-cppmd
        PATHS /usr/lib  /usr/local/lib ${YAMLCPP_INSTALL_PREFIX}/lib ${YAMLCPP_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

#message("YAMLCPP_INCLUDE_DIR ${YAMLCPP_INCLUDE_DIR}")
#message("YAMLCPP_LIBRARY_DEBUG ${YAMLCPP_LIBRARY_DEBUG}")

if(YAMLCPP_INCLUDE_DIR AND (YAMLCPP_LIBRARY_DEBUG OR YAMLCPP_LIBRARY_RELEASE))
    set(YAMLCPP_FOUND TRUE)
endif()

if(YAMLCPP_FOUND)
    if(NOT YAMLCPP_FIND_QUIETLY)
        message(STATUS "Found yaml-cpp debug: ${YAMLCPP_LIBRARY_DEBUG}")
        message(STATUS "Found yaml-cpp release: ${YAMLCPP_LIBRARY_RELEASE}")
    endif()
else()
    if(YAMLCPP_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find yaml-cpp library")
    endif()
endif()
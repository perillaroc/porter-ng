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

if(VS_CONFIGURATION_TYPE STREQUAL "Debug")
	message("Debug")
	set(YAML_LIBRARY_NAMES
		yaml-cpp
		libyaml-cppmdd
	)
else()
	message("Not Debug ${VS_CONFIGURATION_TYPE}")
	set(YAML_LIBRARY_NAMES
		yaml-cpp
		libyaml-cppmdd
	)
endif()

find_library(
        YAMLCPP_LIBRARY
        NAMES ${YAML_LIBRARY_NAMES}
        PATHS /usr/lib  /usr/local/lib ${YAMLCPP_INSTALL_PREFIX}/lib ${YAMLCPP_LIBRARY_DIR}
        NO_DEFAULT_PATH
)

message("YAMLCPP_INCLUDE_DIR ${YAMLCPP_INCLUDE_DIR}")
message("YAMLCPP_LIBRARY ${YAMLCPP_LIBRARY}")

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
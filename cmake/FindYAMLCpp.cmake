if(YAMLCPP_INSTALL_PREFIX)
    set(YAMLCpp_INCLUDE_HINTS ${YAMLCPP_INSTALL_PREFIX}/include)
    set(YAMLCpp_LIBRARY_HINTS ${YAMLCPP_INSTALL_PREFIX}/lib)
endif()

find_path(
    YAMLCpp_INCLUDE_DIR
    NAMES yaml-cpp/yaml.h
    PATHS /usr/include /usr/local/include ${YAMLCPP_INSTALL_PREFIX}/include
    NO_DEFAULT_PATH)

find_library(
    YAMLCpp_LIBRARY_DEBUG
    NAMES yaml-cppd libyaml-cppmdd
    PATHS /usr/lib  /usr/local/lib ${YAMLCPP_INSTALL_PREFIX}/lib ${YAMLCpp_LIBRARY_DIR}
    NO_DEFAULT_PATH)

find_library(
    YAMLCpp_LIBRARY_RELEASE
    NAMES yaml-cpp libyaml-cppmd
    PATHS /usr/lib  /usr/local/lib ${YAMLCPP_INSTALL_PREFIX}/lib ${YAMLCpp_LIBRARY_DIR}
    NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
if(MSVC)
    find_package_handle_standard_args(YAMLCpp
        REQUIRED_VARS YAMLCpp_INCLUDE_DIR YAMLCpp_LIBRARY_DEBUG YAMLCpp_LIBRARY_RELEASE)
else()
    find_package_handle_standard_args(YAMLCpp
        REQUIRED_VARS YAMLCpp_INCLUDE_DIR YAMLCpp_LIBRARY_RELEASE)
endif()

if(YAMLCpp_FOUND AND NOT TARGET YAMLCpp::YAMLCpp)
    add_library(YAMLCpp::YAMLCpp UNKNOWN IMPORTED)

    if(YAMLCpp_LIBRARY_RELEASE)
        set_property(TARGET YAMLCpp::YAMLCpp APPEND PROPERTY
            IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(YAMLCpp::YAMLCpp PROPERTIES
            IMPORTED_LOCATION_RELEASE "${YAMLCpp_LIBRARY_RELEASE}")
    endif()

    if(YAMLCpp_LIBRARY_DEBUG)
        set_property(TARGET YAMLCpp::YAMLCpp APPEND PROPERTY
            IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(YAMLCpp::YAMLCpp PROPERTIES
            IMPORTED_LOCATION_DEBUG "${YAMLCpp_LIBRARY_DEBUG}")
    else()
        set_target_properties(YAMLCpp::YAMLCpp PROPERTIES
            IMPORTED_LOCATION_DEBUG "${YAMLCpp_LIBRARY_RELEASE}")
    endif()

    set_target_properties(YAMLCpp::YAMLCpp PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
        INTERFACE_INCLUDE_DIRECTORIES "${YAMLCpp_INCLUDE_DIR}"
        )
    mark_as_advanced(
        YAMLCpp_INCLUDE_DIR
        YAMLCpp_LIBRARY_DEBUG
        YAMLCpp_LIBRARY_RELEASE
    )
else()
    if(YAMLCpp_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find yaml-cpp library")
    endif()
endif()
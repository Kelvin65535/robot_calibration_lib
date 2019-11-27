cmake_minimum_required(VERSION 3.15)
project(calibration)

# From http://www.cmake.org/pipermail/cmake/2010-March/035992.html:
# function to collect all the sources from sub-directories
# into a single list
function(add_sources)
    get_property(is_defined GLOBAL PROPERTY SRCS_LIST DEFINED)
    if (NOT is_defined)
        define_property(GLOBAL PROPERTY SRCS_LIST
                BRIEF_DOCS "List of source files"
                FULL_DOCS "List of all source files in the entire project")
    endif ()
    # make absolute paths
    set(SRCS)
    foreach (s IN LISTS ARGN)
        if (NOT IS_ABSOLUTE "${s}")
            get_filename_component(s "${s}" ABSOLUTE)
        endif ()
        list(APPEND SRCS "${s}")
    endforeach ()
    # append to global list
    set_property(GLOBAL APPEND PROPERTY SRCS_LIST "${SRCS}")
endfunction(add_sources)

set(header_directory "include/calibration")
file(GLOB sources "src/[a-zA-Z]*.cpp")
file(GLOB_RECURSE public_headers "${header_directory}/[a-zA-Z]*.h")

# source
set(library_sources
        ${sources}
        ${public_headers}
        )
add_sources(${library_sources})

if (VERBOSE)
    message(STATUS "library sources: ${sources}")
    message(STATUS "public_headers: ${public_headers}")
    message(STATUS "project_source_dir: ${calibration_SOURCE_DIR}")
endif ()

# include
set(INCLUDE_INSTALL_ROOT_DIR include)
set(INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_ROOT_DIR})
set(LIB_INSTALL_DIR "lib${LIB_SUFFIX}")
set(_INSTALL_DESTINATIONS
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        )


# create library target
add_library(calibration STATIC ${library_sources})

# library target properties
set_target_properties(calibration PROPERTIES
        VERSION "${CALIBRATION_VERSION_MAJOR}"
        SOVERSION "${CALIBRATION_VERSION_MAJOR}.${CALIBRATION_VERSION_MINOR}"
        )

# include
if (CMAKE_VERSION VERSION_LESS 2.8.12)
    include_directories(${calibration_SOURCE_DIR}/include)
endif ()
if (NOT CMAKE_VERSION VERSION_LESS 2.8.12)
    target_include_directories(calibration
            PUBLIC $<BUILD_INTERFACE:${calibration_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${INCLUDE_INSTALL_ROOT_DIR}>)
endif ()

# link
target_link_libraries(calibration ${OpenCV_LIBS} yaml-cpp)
if (NOT APPLE)
    target_link_libraries(calibration stdc++fs)
endif ()

# install library
install(
        TARGETS calibration
        EXPORT calibration-targets
        ${_INSTALL_DESTINATIONS}
)
# install header
install(
        DIRECTORY ${header_directory}
        DESTINATION ${INCLUDE_INSTALL_DIR}
        FILES_MATCHING PATTERN "*.h"
)

# generate calibration-config.cmake in binary dir
set(CONFIG_INCLUDE_DIRS "${calibration_SOURCE_DIR}/include")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/calibration-config.cmake.in
        "${PROJECT_BINARY_DIR}/calibration-config.cmake" @ONLY)


# generate calibration-target.cmake
export(
        TARGETS calibration
        FILE "${PROJECT_BINARY_DIR}/calibration-targets.cmake")
export(PACKAGE calibration)
set(CALIBRATION_EXPORT_TARGETS calibration "calibration export targets")

# install
# generate calibration-config.cmake in install dir
# calibration-config.cmake install location
set(INSTALL_CMAKE_DIR ${LIB_INSTALL_DIR}/cmake/calibration)
# CALIBRATION_CMAKE_DIR: calibration-config.cmake file location written in calibration-config.cmake

# include header install location
file(RELATIVE_PATH REL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/${INSTALL_CMAKE_DIR}" "${CMAKE_INSTALL_PREFIX}/${INCLUDE_INSTALL_ROOT_DIR}")
set(CONFIG_INCLUDE_DIRS "\${CALIBRATION_CMAKE_DIR}/${REL_INCLUDE_DIR}")

if (VERBOSE)
    message(STATUS "Generating calibration-config.cmake")
    message(STATUS "INSTALL_CMAKE_DIR: " ${INSTALL_CMAKE_DIR})
    message(STATUS "related between INSTALL_CMAKE_DIR to CONFIG_INCLUDE_DIRS: " ${REL_INCLUDE_DIR})
    message(STATUS "CONFIG_INCLUDE_DIRS: " ${CONFIG_INCLUDE_DIRS})
endif ()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/calibration-config.cmake.in
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/calibration-config.cmake" @ONLY)

# install calibration-config.cmake
# use .cmake in find_package()
install(FILES
        "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/calibration-config.cmake"
        DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
# install calibration-target.cmake
install(EXPORT calibration-targets DESTINATION ${INSTALL_CMAKE_DIR})
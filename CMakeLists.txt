cmake_minimum_required(VERSION 3.15)
project(robot_calibration_lib)

# version
set (CALIBRATION_VERSION_MAJOR 1)
set (CALIBRATION_VERSION_MINOR 0)

# compiler
set(CMAKE_CXX_STANDARD 11)

# set platform
if (APPLE)
    message("platform APPLE")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")
    set(OpenCV_DIR /usr/local/Cellar/opencv@3/3.4.5_6/share/OpenCV)
else()
    message("platform LINUX")
    set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev)
endif ()

# include 3rd party library
include(${PROJECT_SOURCE_DIR}/cmake/third_party_import.cmake)

# general option
OPTION(CALIBRATION_ENABLE_TEST "include test execute file" ON)
OPTION(VERBOSE "verbose mode" ON)

configure_file(
        "cmake/cmake-config.h.in"
        "${PROJECT_BINARY_DIR}/include/cmake-config.h"
)

# google test
if (CALIBRATION_ENABLE_TEST)
    add_subdirectory(test)
endif()

# calibration
add_subdirectory(calibration)

# example code
#add_subdirectory(example)
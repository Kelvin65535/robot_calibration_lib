cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
#find_package(OpenCV REQUIRED)
# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})

# Eigen 3
find_package(Eigen3 REQUIRED)
include_directories($(EIGEN3_INCLUDE_DIR))


add_executable(simple_opencv_example simple_opencv_example.cpp)
target_link_libraries(simple_opencv_example ${OpenCV_LIBS})
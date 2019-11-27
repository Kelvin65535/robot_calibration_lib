# googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/third-party/googletest-1.8.0
)
FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

# yaml
FetchContent_Declare(
        yaml-cpp
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/third-party/yaml-cpp-0.6.3
)
FetchContent_GetProperties(yaml-cpp)
if (NOT yaml-cpp_POPULATED)
    FetchContent_Populate(yaml-cpp)
    option(YAML_CPP_BUILD_TESTS OFF)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif ()

# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Eigen 3
find_package(Eigen3 REQUIRED)
include_directories($(EIGEN3_INCLUDE_DIR))
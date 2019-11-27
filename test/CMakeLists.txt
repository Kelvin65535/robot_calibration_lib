cmake_minimum_required(VERSION 3.15)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${OpenCV_LIBS} yaml-cpp calibration)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

include_directories(${PROJECT_BINARY_DIR}/include)
# library header
include_directories(${PROJECT_SOURCE_DIR}/calibration/include)

aux_source_directory(. DIR_TEST_SRCS)

#package_add_test(unit_test ${DIR_TEST_SRCS})
add_executable(unit_test ${DIR_TEST_SRCS})
link_directories(${OpenCV_LIBS})
target_link_libraries(unit_test gtest gmock gtest_main ${OpenCV_LIBS} yaml-cpp calibration)
# gcc
if (NOT APPLE)
    target_link_libraries(unit_test stdc++fs)
endif ()

add_test(NAME unit_test COMMAND unit_test)
set_target_properties(unit_test PROPERTIES FOLDER tests)
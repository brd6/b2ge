# base configuration
cmake_minimum_required(VERSION 3.0)
project(b2geTest)

set(GTEST_LIB_DIR ext/googletest)

add_subdirectory(${GTEST_LIB_DIR})

include_directories(${GTEST_LIB_DIR}/googletest/include)
include_directories(${GTEST_LIB_DIR}/googlemock/include)

file(GLOB TEST_SOURCE_FILES *.cpp)
#set(TEST_SOURCE_FILES gtest.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} gmock gmock_main)

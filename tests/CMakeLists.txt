# base configuration
cmake_minimum_required(VERSION 3.0)
project(b2getest)

set(GTEST_LIB_DIR external/googletest)
#set(GTEST_LIB_DIR ../external/googletest/googletest CACHE STRING "Google Test source root")

add_subdirectory(${GTEST_LIB_DIR})

include_directories(${GTEST_LIB_DIR}/googletest/include)
#include_directories(${GTEST_LIB_DIR}/googlemock/include)

include_directories(${CMAKE_SOURCE_DIR}/include)
#include_directories(${CMAKE_SOURCE_DIR}/src/b2ge/Core)
#include_directories(${CMAKE_SOURCE_DIR}/src/b2ge/Manager)
#include_directories(${CMAKE_SOURCE_DIR}/src/b2ge/Util)

file(GLOB TEST_SOURCE_FILES *.cpp)
#set(TEST_SOURCE_FILES gtest.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
#target_link_libraries(${PROJECT_NAME} gmock gmock_main)
target_link_libraries(${PROJECT_NAME} b2ge)
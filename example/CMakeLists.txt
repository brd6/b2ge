# base configuration
cmake_minimum_required(VERSION 3.0)
project(example)

file(GLOB SOURCE_FILES *.cpp)

include_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} b2ge)

# base configuration
cmake_minimum_required(VERSION 3.0)
project(b2ge)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

# source files
set(SOURCE_FILES src/b2ge/Util/Debug.cpp)

set(B2GE_INCLUDE include/b2ge)
include_directories(${B2GE_INCLUDE})

# Lib configuration
add_library(b2ge STATIC ${SOURCE_FILES})

install(DIRECTORY ${B2GE_INCLUDE} DESTINATION .)
install(TARGETS ${PROJECT_NAME} DESTINATION .)
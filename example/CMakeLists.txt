
# Setting
#set(ENABLE_BUILD_TESTS true)

# base configuration
cmake_minimum_required(VERSION 3.0)
project(example)

set(CMAKE_CXX_STANDARD 14)

# Enable flag for dev
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -DDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

#set(ENABLE_BUILD_TESTS true)
# cmake -DCMAKE_INSTALL_PREFIX=/usr . && make all install

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

# Unit test
#if (ENABLE_BUILD_TESTS)
#    enable_testing()
#    add_subdirectory(tests)
#endif()

#add_subdirectory(example)

# cmake modules path
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SFML REQUIRED graphics window audio system)
find_package(B2GE REQUIRED)

# Include directory
set(EXAMPLE_INCLUDE ${CMAKE_SOURCE_DIR}/include)
include_directories(${SFML_INCLUDE_DIR} ${B2GE_INCLUDE_DIR} ${EXAMPLE_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})
#set(SOURCE_FILES ${SOURCE_FILES})

# Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link library
target_link_libraries(${PROJECT_NAME} ${B2GE_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# Install
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION .)
#install(DIRECTORY assets
#        DESTINATION .)
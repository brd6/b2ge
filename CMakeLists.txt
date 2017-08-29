
# Setting
set(ENABLE_BUILD_TESTS true)

# base configuration
cmake_minimum_required(VERSION 3.0)
project(b2ge)

set(CMAKE_CXX_STANDARD 14)

# cmake -DCMAKE_INSTALL_PREFIX=/usr . && make all install

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
endif()

# Unit test
if (ENABLE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#########################################

# Include directory
set(B2GE_INCLUDE include/b2ge)
include_directories(${B2GE_INCLUDE})

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# Source files
set(SOURCE_FILES ${SOURCE_FILES} ${INCLUDE_FILES})

# Lib configuration
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})


# Executable
#add_executable(${PROJECT_NAME}-bin ${SOURCE_FILES})
#target_link_libraries(${PROJECT_NAME}-bin ${PROJECT_NAME})
#set_target_properties(${PROJECT_NAME}-bin
#        PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# Install lib
install(DIRECTORY ${B2GE_INCLUDE} DESTINATION lib)
#install(TARGETS ${PROJECT_NAME} DESTINATION lib)
INSTALL(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.2)

# Project's name 
project(PSU)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

include_directories("/usr/local/include")

link_directories("/usr/local/lib")
  
add_executable(test_PSU test/test_PSU.cpp)
target_link_libraries(test_PSU libmcl.a libgmp.a)

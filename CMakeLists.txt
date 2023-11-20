cmake_minimum_required(VERSION 3.16)
project(solution)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_BUILD_TYPE Debug)

# include
include_directories(${PROJECT_SOURCE_DIR}/include/)
# link link_directories()

file(GLOB_RECURSE CUSTOM_SRC_FILE src/*.cpp)
add_library(custom SHARED ${CUSTOM_SRC_FILE})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} custom)

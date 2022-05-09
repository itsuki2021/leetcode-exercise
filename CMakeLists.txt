cmake_minimum_required(VERSION 3.16)
project(solution)

set(CMAKE_CXX_STANDARD 11)

# include
include_directories(
    ${PROJECT_SOURCE_DIR}/include/
)
# link
# link_directories()

file(GLOB_RECURSE CUSTOM_SRC_FILE src/*.cpp)
add_library(custom SHARED ${CUSTOM_SRC_FILE})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} custom)
cmake_minimum_required(VERSION 3.0)

project(maze C)

file(GLOB sources src/* include/*)

add_library(${PROJECT_NAME} STATIC ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -g -Wall)
target_include_directories(${PROJECT_NAME} PRIVATE include)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

add_subdirectory(./cli)
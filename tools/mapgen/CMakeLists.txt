cmake_minimum_required(VERSION 3.0)

project(mapgen C)

file(GLOB sources *.c *.h)

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)

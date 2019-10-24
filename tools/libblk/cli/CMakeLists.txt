cmake_minimum_required(VERSION 3.0)

project(libblk-cli C)

file(GLOB sources *.c *.h)

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)
target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_link_libraries(${PROJECT_NAME} PRIVATE blk)
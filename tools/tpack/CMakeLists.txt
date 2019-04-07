cmake_minimum_required(VERSION 3.0)

project(tpack C)

file(GLOB sources src/*)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PNG REQUIRED libpng)

link_directories(${PROJECT_NAME} PRIVATE ${PNG_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)
target_include_directories(${PROJECT_NAME} PRIVATE ${PNG_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE png)

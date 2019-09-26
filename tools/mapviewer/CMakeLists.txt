cmake_minimum_required(VERSION 3.0)

project(mapviewer C)

file(GLOB sources *.c *.h)

find_package(PkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

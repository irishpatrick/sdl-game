cmake_minimum_required(VERSION 3.0)

project(sdl-game)

#option(RELEASE "Build release binary" OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

file(GLOB sources src/*.cc)
add_executable(a ${sources})

target_link_libraries(a -pthread ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_include_directories(a PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

if (RELEASE)
    target_compile_options(a PUBLIC -std=c++11 -s -O3 -funroll-loops)
else ()
    target_compile_options(a PUBLIC -std=c++11 -Wall -g -Og)
endif (RELEASE)

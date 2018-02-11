cmake_minimum_required(VERSION 3.0)

project(sdl-game)

if (UNIX)
    set(SDL2_INC_DIR "/usr/include/SDL2" CACHE STRING "include dirs")
    set(SDL2_LIB_DIR "/usr/lib/x86_64-linux-gnu" CACHE STRING "library dirs")
endif (UNIX)

if (MSVC)
    set(SDL2_INC_DIR "" CACHE STRING "")
    set(SDL2_LIB_DIR "" CACHE STRING "")
endif (MSVC)

find_library(SDL2_LIB NAMES SDL2 PATHS ${SDL2_LIB_DIR})
find_library(SDL2_IMAGE_LIB NAMES SDL2_image PATHS ${SDL2_LIB_DIR})
find_library(SDL2_TTF_LIB NAMES SDL2_ttf PATHS ${SDL2_LIB_DIR})

add_subdirectory(engine)
add_subdirectory(rpg)
add_subdirectory(missiles)

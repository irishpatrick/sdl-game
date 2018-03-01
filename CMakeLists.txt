cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)

if (UNIX)
    set(SDL_INCLUDE_DIR "/usr/include/SDL2" CACHE STRING "include dirs")
    set(SDL_LIBRARY_DIR "/usr/lib/" CACHE STRING "library dirs")
endif (UNIX)

if (MSVC)
    set(SDL_INCLUDE_DIR "" CACHE STRING "")
    set(SDL_LIBRARY_DIR "" CACHE STRING "")
endif (MSVC)

set(SDL_LIBRARIES "-lSDL2 -lSDL2_image -lSDL2_ttf" CACHE STRING "string")

add_subdirectory(engine)
if (BUILD_RPG)
    add_subdirectory(rpg)
endif(BUILD_RPG)
    
if (BUILD_MISSILES)
    add_subdirectory(missiles)
endif(BUILD_MISSILES)


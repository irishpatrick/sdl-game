cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)

if (UNIX)
    set(INCLUDE_DIR "/usr/include/" CACHE STRING "include dirs")
    set(LIBRARY_DIR "/usr/lib/" CACHE STRING "library dirs")
else(UNIX)
    set(INCLUDE_DIR "" CACHE STRING "")
    set(LIBRARY_DIR "" CACHE STRING "")
endif (UNIX)

set(SDL_LIBRARIES "-lSDL2 -lSDL2_image -lSDL2_ttf" CACHE STRING "string")

add_subdirectory(engine)
if (BUILD_RPG)
    add_subdirectory(rpg)
endif(BUILD_RPG)

if (BUILD_MISSILES)
    add_subdirectory(missiles)
endif(BUILD_MISSILES)

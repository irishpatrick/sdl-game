cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)
option (BUILD_RUNNER "build runner game" OFF)

set(SDL_LIBRARIES "SDL2;SDL2_image;SDL2_ttf" CACHE STRING "string")

if (UNIX)
    set(INCLUDE_DIR "/usr/include/" CACHE STRING "include dirs")
    set(LIBRARY_DIR "/usr/lib/" CACHE STRING "library dirs")
else(UNIX)
    set(INCLUDE_DIR "" CACHE STRING "")
    set(LIBRARY_DIR "" CACHE STRING "")
endif (UNIX)

add_subdirectory(engine)

if (BUILD_RPG)
    add_subdirectory(rpg)
endif (BUILD_RPG)

if (BUILD_MISSILES)
    add_subdirectory(missiles)
endif (BUILD_MISSILES)

if (BUILD_RUNNER)
    add_subdirectory(runner)
endif (BUILD_RUNNER)

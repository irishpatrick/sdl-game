cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)
option (BUILD_RUNNER "build runner game" OFF)

set(SDL_LIBRARIES "SDL2;SDL2_image;SDL2_ttf" CACHE STRING "string")
set(COMPILE_OPTIONS "")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
    set(INCLUDE_DIR "/usr/include/" CACHE PATH "include dirs")
    set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")
    set(LINK_OPTIONS "-pthread -llua")
else(UNIX)
    set(INCLUDE_DIR "" CACHE PATH "")
    set(LIBRARY_DIR "" CACHE PATH "")
    set(LINK_OPTIONS "")
endif (UNIX)

add_subdirectory(libs/engine)
add_subdirectory(libs/particles)
add_subdirectory(libs/gui)

if (BUILD_RPG)
    add_subdirectory(games/rpg)
endif (BUILD_RPG)

if (BUILD_MISSILES)
    add_subdirectory(games/missiles)
endif (BUILD_MISSILES)

if (BUILD_RUNNER)
    add_subdirectory(games/runner)
endif (BUILD_RUNNER)

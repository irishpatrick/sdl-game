cmake_minimum_required(VERSION 3.0)

project(sdl-game)

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
add_subdirectory(rpg)
add_subdirectory(missiles)

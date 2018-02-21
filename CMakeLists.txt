cmake_minimum_required(VERSION 3.0)

project(sdl-game)

if (UNIX)
    message(STATUS "Unix")
    set(SDL2_INC_DIR "/usr/include/SDL2" CACHE STRING "include dirs")
    set(SDL2_LIB_DIR "/usr/lib/" CACHE STRING "library dirs")
endif (UNIX)

if (MSVC)
    set(SDL2_INC_DIR "" CACHE STRING "")
    set(SDL2_LIB_DIR "" CACHE STRING "")
endif (MSVC)

set(SDL2_LIBS "-lSDL2 -lSDL2_image -lSDL2_ttf" CACHE STRING "string")

message(STATUS "${SDL2_INC_DIR}")
message(STATUS "${SDL2_LIB_DIR}")

add_subdirectory(engine)
add_subdirectory(rpg)
add_subdirectory(missiles)

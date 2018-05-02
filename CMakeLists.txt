cmake_minimum_required(VERSION 3.0)

include("cmake/HunterGate.cmake")

option(HUNTER_BUILD_SHARED_LIBS "build shared libs" ON)

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.20.62.tar.gz"
    SHA1 "10ffae63cf7b07193d6d7b459c1d0cfa242fad5b"
)

project(sdl-game)

hunter_add_package(SDL2)
hunter_add_package(SDL_image)
hunter_add_package(SDL_ttf)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL_image CONFIG REQUIRED)
find_package(SDL_ttf CONFIG REQUIRED)

option (USE_PKGCONFIG "use pkg-config" OFF)
option (USE_HUNTER "use hunter" ON)
option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)
option (BUILD_RUNNER "build runner game" OFF)
option (BUILD_NEWGAME "build garden" OFF)
option (BUILD_PARTICLES "build particles library" OFF)
option (BUILD_GUI "build gui library" OFF)
option (DEBUG_SYMBOLS "enable debug symbols" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

if (USE_PKGCONFIG)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(cairo REQUIRED cairo)
    pkg_check_modules(sdl2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

elseif (USE_HUNTER)

    set(LIBRARIES "SDL2::SDL2main;SDL2::SDL2;SDL_image::SDL_image;SDL_ttf::SDL_ttf;m" CACHE STRING "string")
    if (UNIX)
        message(STATUS "UNIX")
        set(INCLUDE_DIR "/usr/include/" CACHE PATH "include dirs")
        set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "-std=c++17;-Wall;-D_REENTRANT;-O2;")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};-g)
        endif (DEBUG_SYMBOLS)

    elseif (MSVC)
        message(STATUS "MSVC")
        set(INCLUDE_DIR "" CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "/std:c++17;/Wall;/D_REENTRANT;/O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};/DEBUG)
        endif (DEBUG_SYMBOLS)

    else (UNIX)
        message(STATUS "UNKNOWN PLATFORM")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "-std=c++17;-Wall;-D_REENTRANT;-O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};-g)
        endif (DEBUG_SYMBOLS)
    endif (UNIX)

else (USE_PKGCONFIG)

    set(LIBRARIES "SDL2;SDL2_image;SDL2_ttf;m" CACHE STRING "string")

    if (UNIX)
        message(STATUS "UNIX")
        set(INCLUDE_DIR "/usr/include/" CACHE PATH "include dirs")
        set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "-std=c++17;-Wall;-D_REENTRANT;-O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};-g)
        endif (DEBUG_SYMBOLS)

    elseif (MSVC)
        message(STATUS "MSVC")
        set(INCLUDE_DIR "" CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "/std:c++17;/Wall;/D_REENTRANT;/O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};/DEBUG)
        endif (DEBUG_SYMBOLS)

    else (UNIX)
        message(STATUS "UNKNOWN PLATFORM")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "-std=c++17;-Wall;-D_REENTRANT;-O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};-g)
        endif (DEBUG_SYMBOLS)
    endif (UNIX)

endif (USE_PKGCONFIG)

add_subdirectory(libs/engine)
set(MY_LIBS engine)

if (BUILD_PARTICLES)
    add_subdirectory(libs/particles)
    set(MY_LIBS ${MY_LIBS};particles)
endif (BUILD_PARTICLES)

if (BUILD_GUI)
    add_subdirectory(libs/gui)
    set(MY_LIBS ${MY_LIBS};gui)
endif (BUILD_GUI)

if (BUILD_RPG)
    add_subdirectory(games/rpg)
endif (BUILD_RPG)

if (BUILD_MISSILES)
    add_subdirectory(games/missiles)
endif (BUILD_MISSILES)

if (BUILD_RUNNER)
    add_subdirectory(games/runner)
endif (BUILD_RUNNER)

if (BUILD_NEWGAME)
    add_subdirectory(games/newgame)
endif (BUILD_NEWGAME)

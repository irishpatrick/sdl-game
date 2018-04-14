cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (USE_PKGCONFIG "use pkg-config" OFF)
option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)
option (BUILD_RUNNER "build runner game" OFF)
option (BUILD_GARDEN "build garden" OFF)
option (BUILD_PARTICLES "build particles library" ON)
option (BUILD_GUI "build gui library" ON)
option (DEBUG_SYMBOLS "enable debug symbols" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (USE_PKGCONFIG)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(cairo REQUIRED cairo)
    pkg_check_modules(sdl2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

else (USE_PKGCONFIG)

    set(LIBRARIES "SDL2;SDL2_image;SDL2_ttf;" CACHE STRING "string")

    if (UNIX)
        set(INCLUDE_DIR "/usr/include/" CACHE PATH "include dirs")
        set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "-std=c++17;-Wall;-D_REENTRANT;-O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};-g)
        endif (DEBUG_SYMBOLS)
    endif (UNIX)

    if (MSVC)
        set(INCLUDE_DIR "" CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "/std:c++17;/Wall;/D_REENTRANT;/O2")
        if (DEBUG_SYMBOLS)
            set(COMPILE_OPTIONS ${COMPILE_OPTIONS};/DEBUG)
        endif (DEBUG_SYMBOLS)
    endif (MSVC)

endif (USE_PKGCONFIG)

message(INFO ${COMPILE_OPTIONS})

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

if (BUILD_GARDEN)
    add_subdirectory(games/newgame)
endif (BUILD_GARDEN)

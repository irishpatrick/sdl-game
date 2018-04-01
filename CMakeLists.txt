cmake_minimum_required(VERSION 3.0)

project(sdl-game)

option (USE_PKGCONFIG "use pkg-config" OFF)
option (BUILD_MISSILES "build missiles game" OFF)
option (BUILD_RPG "build rpg game" OFF)
option (BUILD_RUNNER "build runner game" OFF)

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
        set(COMPILE_OPTIONS "-std=c++14;-Wall;-D_REENTRANT;-O2")
    endif (UNIX)

    if (MSVC)
        set(INCLUDE_DIR "" CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")
        set(LINK_OPTIONS "")
        set(COMPILE_OPTIONS "/std:c++14;/Wall;/D_REENTRANT;/O2")
    endif (MSVC)

endif (USE_PKGCONFIG)

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

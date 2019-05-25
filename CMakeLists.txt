cmake_minimum_required(VERSION 3.0)

if (MSVC)

elseif (UNIX)

set(COMPILE_OPTIONS -std=c++11 -g -Wall)

find_package(PkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(CAIRO REQUIRED cairo)

set(INCL
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CAIRO_INCLUDE_DIRS})

set(LIBS
    ${SDL2_LIBS} 
    ${SDL2_IMAGE_LIBS}
    ${SDL2_TTF_LIBS}
    ${CAIRO_LIBS}
    stdc++fs)

endif (MSVC)

add_subdirectory(./engine)
add_subdirectory(./rpg)

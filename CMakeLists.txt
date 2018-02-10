cmake_minimum_required(VERSION 3.0)

project(sdl-game)

if (UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
endif (UNIX)

if (MSVC)

endif (MSVC)

set(SDL2_INC_DIRS "/usr/include/SDL2" CACHE STRING "SDL2 include dirs")
set(SDL2_LIB_DIRS "/usr/lib/")

add_subdirectory(engine)
add_subdirectory(rpg)
add_subdirectory(missiles)

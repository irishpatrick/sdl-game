cmake_minimum_required(VERSION 3.0)

if (MSVC)

set(COMPILE_OPTIONS /DEBUG /W3)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(unofficial-cairo CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_path(CAIRO_INCLUDE_DIR NAMES cairo.h PATH_SUFFIXES cairo)

set(INCL
	${CAIRO_INCLUDE_DIR})

set(LIBS
	SDL2::SDL2
	SDL2::SDL2main
	SDL2::SDL2_image
	SDL2::SDL2_ttf
	unofficial::cairo::cairo
	unofficial::cairo::cairo-gobject
	nlohmann_json
	nlohmann_json::nlohmann_json
	bcrypt
	)

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
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${CAIRO_LIBRARIES}
    stdc++fs
    freetype)

endif (MSVC)

add_subdirectory(./engine)
add_subdirectory(./rpg)
add_subdirectory(./platformer)
add_subdirectory(./roguelike)

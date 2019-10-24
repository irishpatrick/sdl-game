cmake_minimum_required(VERSION 3.0)

project(sdl-game)

if (MSVC)

if (_DEBUG)

message(STATUS "DEBUG")
set(COMPILE_OPTIONS /DEBUG /W3 /D_DEBUG /MDd)

elseif (_RELEASE)

message(STATUS "RELEASE")
set (COMPILE_OPTIONS /W3 /D_RELEASE /MD)

endif ()

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(sdl2-ttf CONFIG REQUIRED)
find_package(unofficial-cairo CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_path(CAIRO_INCLUDE_DIR NAMES cairo.h PATH_SUFFIXES cairo)
find_path(PANGO_INCLUDE_DIR NAMES pango.h PATH_SUFFIXES pango)

find_library(BCRYPT NAMES bcrypt)
find_library(GOBJECT NAMES gobject-2.0)
find_library(PANGOCAIRO NAMES pangocairo-1.0)
find_library(PANGO NAMES pango-1.0)
find_library(LUA NAMES lua)

set(INCL
    3rdparty
	${CAIRO_INCLUDE_DIR}
    ${PANGO_INCLUDE_DIR}
)

set(LIBS
	SDL2::SDL2
	SDL2::SDL2main
	SDL2::SDL2_image
	SDL2::SDL2_ttf
	unofficial::cairo::cairo
	unofficial::cairo::cairo-gobject
	nlohmann_json
	nlohmann_json::nlohmann_json
    ${BCRYPT}
    ${GOBJECT}
    ${PANGOCAIRO}
    ${PANGO}
    ${LUA}
)

elseif (UNIX)

set(COMPILE_OPTIONS -std=c++11 -g -Wall)

find_package(PkgConfig)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(PANGOCAIRO REQUIRED pangocairo)
pkg_check_modules(LUA REQUIRED lua5.2)

set(INCL
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${CAIRO_INCLUDE_DIRS}
    ${PANGO_INCLUDE_DIRS}
    ${PANGOCAIRO_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIRS}
)

set(LIBS
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${PANGO_LIBRARIES}
    ${PANGOCAIRO_LIBRARIES}
    ${LUA_LIBRARIES}
    stdc++fs
    freetype
)

endif (MSVC)

add_subdirectory(./engine)
add_subdirectory(./tools/libmaze)
add_subdirectory(./tools/libblk)
add_subdirectory(./rpg)
add_subdirectory(./platformer)
add_subdirectory(./roguelike)
add_subdirectory(./tennis)

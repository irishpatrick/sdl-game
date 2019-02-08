cmake_minimum_required(VERSION 3.0)

# set options
option (USE_HUNTER "use hunter" OFF)
option (HUNTER_BUILD_SHARED_LIBS "hunter build shared libs" ON)
option (USE_PKGCONFIG "use pkg-config" OFF)
option (BUILD_RPG "build game" OFF)
option (BUILD_RASPBERRY_GAME "raspberry game" OFF)
option (BUILD_STRATEGY_GAME "strategy game" OFF)
option (DEBUG_SYMBOLS "enable debug symbols" ON)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# set variables
set(COMPILE_OPTIONS "")
set(LINK_OPTIONS "")
set(MSVC_INCLUDE "" CACHE PATH "")
set(MSVC_LIB "" CACHE PATH "")
set(INCLUDE_DIR "lib/include")

# initialize hunter
if (USE_HUNTER)
	include("cmake/HunterGate.cmake")
    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.7.tar.gz"
        SHA1 "183d23691c5bb2e3053bd6a7ad6021d16b24664d"
    )
endif (USE_HUNTER)

# begin project
project(sdl-game)

# we're on windows
if (MSVC)

	set(LIBRARIES ${LIBRARIES})

    message(STATUS "MSVC")

	if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /DEBUG /Od)
    endif (DEBUG_SYMBOLS)

    set(COMPILE_OPTIONS /std:c++14 /W3 /D_REENTRANT /Od /MP)
    set(INCLUDE_DIR ${INCLUDE_DIR};${MSVC_INCLUDE};${MSVC_INCLUDE}/SDL2)
	message(STATUS ${INCLUDE_DIR})
    set(LIBRARY_DIR ${LIBRARY_DIR} ${MSVC_LIB})
	set(LIBRARIES ${LIBRARIES} SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib)

# we're probably on linux
elseif (UNIX)

	message(STATUS "UNIX")

	set(INCLUDE_DIR ${INCLUDE_DIR} /usr/include/)
    set(LIBRARY_DIR /usr/lib/)
    set(LIBRARIES ${LIBRARIES} stdc++fs)
    set(COMPILE_OPTIONS -std=c++14 -D_REENTRANT -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pthread)

	if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -g)
	endif (DEBUG_SYMBOLS)

# we have no idea
endif ()

# finding dependencies using hunter
if (USE_HUNTER)

    message(STATUS "using hunter")

    if (UNIX)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -DUSE_HUNTER)
    elseif (MSVC)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /DUSE_HUNTER)
    endif (UNIX)

    hunter_add_package(SDL2)
    hunter_add_package(SDL_image)
    hunter_add_package(SDL_ttf)
    hunter_add_package(cairo)
    hunter_add_package(nlohmann-json)

    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL_image CONFIG REQUIRED)
    find_package(SDL_ttf CONFIG REQUIRED)
    find_package(cairo CONFIG REQUIRED)
    find_package(nlohmann-json CONFIG REQUIRED)

    message(STATUS ${SDL2_ROOT})

    set(LIBRARIES ${LIBRARIES} SDL2::SDL2main SDL2::SDL2 SDL_image::SDL_image SDL_ttf::SDL_ttf  m CACHE STRING "string")
    set(INCLUDE_DIR ${INCLUDE_DIR} ${SDL2_ROOT}/include/SDL2 ${SDL_TTF_ROOT}/include/SDL_ttf)

# finding dependencies using pkg-config
elseif (USE_PKGCONFIG)

    message(STATUS "using pkg-config")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)
    #pkg_check_modules(nlohmann-json REQUIRED json)


    set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/include ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
    set(LIBRARY_DIR ${SDL2_LIBRARY_DIRS} ${SDL2_image_LIBRARY_DIRS} ${SDL2_ttf_LIBRARY_DIRS})
    set(LIBRARIES ${LIBRARIES} SDL2 SDL2_image SDL2_ttf)

# use vcpkg
else ()
    find_package(SDL2 CONFIG REQUIRED)
    find_library(SDL2_IMAGE_LIB SDL2_image REQUIRED)
    find_library(SDL2_TTF_LIB SDL2_ttf REQUIRED)
    find_library(CAIRO_LIB cairo REQUIRED)


    set(LIBRARIES
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_IMAGE_LIB}
        ${SDL2_TTF_LIB}
        ${CAIRO_LIB}
		bcrypt
    )

	find_path(SDL_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)

	set(INCLUDE_DIR
		${INCLUDE_DIR}
		${SDL_INCLUDE_DIR}
	)

endif ()


# add all the projects

add_subdirectory(./engine/core)
set(LIBRARIES ${LIBRARIES} core)

if (BUILD_RPG)
    add_subdirectory(./rpg)
endif (BUILD_RPG)

if (BUILD_RASPBERRY_GAME)
	add_subdirectory(./catch)
endif (BUILD_RASPBERRY_GAME)

if (BUILD_STRATEGY_GAME)
	add_subdirectory(./strategy)
endif (BUILD_STRATEGY_GAME)

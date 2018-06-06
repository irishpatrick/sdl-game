cmake_minimum_required(VERSION 3.0)

option (USE_HUNTER "use hunter" OFF)
option (HUNTER_BUILD_SHARED_LIBS "hunter build shared libs" ON)
option (USE_PKGCONFIG "use pkg-config" OFF)
option (USE_MSVC "use msvc" OFF)
option (BUILD_GAME "build game" ON)
option (BUILD_EDITOR "build editor" ON)
option (DEBUG_SYMBOLS "enable debug symbols" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

set(COMPILE_OPTIONS "")
set(LINK_OPTIONS "")

set(INCLUDE_DIR deps/include CACHE PATH "")

if (USE_HUNTER)
	include("cmake/HunterGate.cmake")
    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.20.74.tar.gz"
        SHA1 "88e3c806f0ff640c0e3cbc32b340ae2c370b31f5"
    )
endif (USE_HUNTER)

project(sdl-game)

if (MSVC)
    message(STATUS "MSVC")
    set(COMPILE_OPTIONS /std:c++14 /W3 /D_REENTRANT /O2 /MP)
    if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /DEBUG /Od)
    endif (DEBUG_SYMBOLS)
elseif (UNIX)
	message(STATUS "UNIX")
    set(COMPILE_OPTIONS -std=c++14 -D_REENTRANT -O2 -Wall -pthread)
    if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -g)
    endif (DEBUG_SYMBOLS)
else (MSVC)
    message(STATUS "UNKNOWN")
    set(COMPILE_OPTIONS -std=c++14 -D_REENTRANT -O2 -Wall)
    if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -g)
    endif (DEBUG_SYMBOLS)
endif (MSVC)

if (USE_HUNTER)
    message(STATUS "using hunter")

    hunter_add_package(Boost COMPONENTS system filesystem)
    hunter_add_package(SDL2)
    hunter_add_package(SDL_image)

    find_package(Boost CONFIG REQUIRED system filesystem)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL_image CONFIG REQUIRED)

    set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/deps/include")
    set(LIBRARIES ${LIBRARIES} Boost::system Boost::filesystem SDL2::SDL2main SDL2::SDL2 SDL_image::SDL_image m CACHE STRING "string")
    if (UNIX)
        message(STATUS "UNIX")
        set(INCLUDE_DIR "${INCLUDE_DIR};/usr/include/" CACHE PATH "include dirs")
        set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")

    elseif (MSVC)
        message(STATUS "MSVC")
        set(INCLUDE_DIR ${INCLUDE_DIR} CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")

    else (UNIX)
        message(STATUS "UNKNOWN PLATFORM")
    endif (UNIX)

endif (USE_HUNTER)

if (USE_PKGCONFIG)

    message(STATUS "using pkg-config")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)

    find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

    set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/include ${Boost_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
    set(LIBRARY_DIR ${SDL2_LIBRARY_DIRS} ${SDL2_image_LIBRARY_DIRS})
    set(LIBRARIES ${LIBRARIES} SDL2 SDL2_image ${Boost_LIBRARIES})

    if (UNIX)
        message(STATUS "UNIX")
        set(INCLUDE_DIR "/usr/include/" CACHE PATH "include dirs")
        set(LIBRARY_DIR "/usr/lib/" CACHE PATH "library dirs")
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -pthread)

    elseif (MSVC)
        message(STATUS "MSVC")
        set(INCLUDE_DIR "" CACHE PATH "")
        set(LIBRARY_DIR "" CACHE PATH "")
        set(LINK_OPTIONS "")

    else (UNIX)
        message(STATUS "UNKNOWN PLATFORM")
    endif (UNIX)

endif (USE_PKGCONFIG)

if (USE_MSVC)
    set(INCLUDE_DIR "" CACHE PATH "")
    set(LIBRARY_DIR "" CACHE PATH "")
    set(LIBRARIES SDL2.lib SDL2main.lib SDL2_image.lib libboost_system-vc140-mt-gd-1_62.lib libboost_filesystem-vc140-mt-gd-1_62.lib)
endif (USE_MSVC)

add_subdirectory(engine/core)
add_subdirectory(engine/ui)
set(MY_LIBS ${MY_LIBS} engine ui)

if (BUILD_GAME)
    add_subdirectory(game)
endif (BUILD_GAME)

if (BUILD_EDITOR)
	add_subdirectory(tools/old)
endif (BUILD_EDITOR)

cmake_minimum_required(VERSION 3.0)

# set options
option (USE_HUNTER "use hunter" OFF)
option (HUNTER_BUILD_SHARED_LIBS "hunter build shared libs" ON)
option (USE_PKGCONFIG "use pkg-config" OFF)
option (BUILD_RPG "build game" ON)
option (BUILD_RASPBERRY_GAME "raspberry game" ON)
option (BUILD_UI "build ui" ON)
option (DEBUG_SYMBOLS "enable debug symbols" ON)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# set variables
set(COMPILE_OPTIONS "")
set(LINK_OPTIONS "")
set(MSVC_INCLUDE "" CACHE PATH "")
set(MSVC_LIB "" CACHE PATH "")
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/include)

# initialize hunter
if (USE_HUNTER)
	include("cmake/HunterGate.cmake")
    HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.20.74.tar.gz"
        SHA1 "88e3c806f0ff640c0e3cbc32b340ae2c370b31f5"
    )
endif (USE_HUNTER)

# begin project
project(sdl-game)

# we're on windows
if (MSVC)

    message(STATUS "MSVC")

	if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /DEBUG /Od)
    endif (DEBUG_SYMBOLS)

    set(COMPILE_OPTIONS /std:c++14 /W3 /D_REENTRANT /Od /MP)
    set(INCLUDE_DIR ${INCLUDE_DIR};${MSVC_INCLUDE};${MSVC_INCLUDE}/SDL2)
	message(STATUS ${INCLUDE_DIR})
    set(LIBRARY_DIR ${LIBRARY_DIR} ${MSVC_LIB})
	set(LIBRARIES SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib libboost_system-vc141-mt-gd-x64-1_67.lib libboost_filesystem-vc141-mt-gd-x64-1_67.lib)

# we're probably on linux
elseif (UNIX)

	message(STATUS "UNIX")

	set(INCLUDE_DIR ${INCLUDE_DIR} /usr/include/)
    set(LIBRARY_DIR /usr/lib/)
    set(COMPILE_OPTIONS -std=c++14 -D_REENTRANT -Wall -pthread)

	if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -g)
	endif (DEBUG_SYMBOLS)

# we have no idea
else (MSVC)

	message(STATUS "UNKNOWN")
    set(COMPILE_OPTIONS -std=c++14 -D_REENTRANT -Wall)
    if (DEBUG_SYMBOLS)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -g)
    endif (DEBUG_SYMBOLS)

endif (MSVC)

# finding dependencies using hunter
if (USE_HUNTER)

    message(STATUS "using hunter")
    
    if (UNIX)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -DUSE_HUNTER)
    elseif (MSVC)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} /DUSE_HUNTER)
    endif (UNIX)

    hunter_add_package(Boost COMPONENTS system filesystem)
    hunter_add_package(SDL2)
    hunter_add_package(SDL_image)
    hunter_add_package(SDL_ttf)

    find_package(Boost CONFIG REQUIRED system filesystem)
    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL_image CONFIG REQUIRED)
    find_package(SDL_ttf CONFIG REQUIRED)
    
    message(STATUS ${SDL2_ROOT})

    set(LIBRARIES ${LIBRARIES} Boost::system Boost::filesystem SDL2::SDL2main SDL2::SDL2 SDL_image::SDL_image SDL_ttf::SDL_ttf m CACHE STRING "string")
    set(INCLUDE_DIR ${INCLUDE_DIR} ${SDL2_ROOT}/include/SDL2 ${SDL_TTF_ROOT}/include/SDL_ttf)

# finding dependencies using pkg-config
elseif (USE_PKGCONFIG)

    message(STATUS "using pkg-config")

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED SDL2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)
    pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

    find_package(Boost 1.58 COMPONENTS system filesystem REQUIRED)

    set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/deps/include ${Boost_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
    set(LIBRARY_DIR ${SDL2_LIBRARY_DIRS} ${SDL2_image_LIBRARY_DIRS} ${SDL2_ttf_LIBRARY_DIRS})
    set(LIBRARIES ${LIBRARIES} SDL2 SDL2_image ${Boost_LIBRARIES})

# we're on our own
else (USE_HUNTER)

endif (USE_HUNTER)


# add all the projects

add_subdirectory(./engine/core)

if (BUILD_UI)
	add_subdirectory(./engine/ui)
endif (BUILD_UI)

if (BUILD_RPG)
    add_subdirectory(./rpg)
endif (BUILD_RPG)

if (BUILD_RASPBERRY_GAME)
	add_subdirectory(./catch)
endif (BUILD_RASPBERRY_GAME)

cmake_minimum_required(VERSION 3.5)

project(sdl-game)

option(BUILD_GAMES "Build Games" ON)

add_subdirectory(engine)
add_subdirectory(rpg)
add_subdirectory(missiles)

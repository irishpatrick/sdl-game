cmake_minimum_required(VERSION 3.5)

project(gui C CXX)

file(GLOB sources src/*.cc)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -std=c++14 -Wall -fPIC -g -D_REENTRANT)
target_link_libraries(${PROJECT_NAME} ${LINK_OPTIONS} ${SDL_LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

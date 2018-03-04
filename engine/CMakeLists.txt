cmake_minimum_required(VERSION 3.0)

project(engine C CXX)

file(GLOB sources src/*.cc)
add_library(${PROJECT_NAME} SHARED ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} "${INCLUDE_DIR}/SDL2" ${engine_INCLUDE_DIRS})
link_directories(${PROJECT_NAME} PUBLIC include ${LIBRARY_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g -D_REENTRANT)
target_link_libraries(${PROJECT_NAME} -pthread ${SDL_LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

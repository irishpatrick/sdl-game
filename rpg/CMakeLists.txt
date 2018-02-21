cmake_minimum_required(VERSION 3.0)

project(rpg C CXX)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL_INCLUDE_DIR} ${engine_INCLUDE_DIRS})
link_directories(${PROJECT_NAME} PUBLIC include ${SDL_LIBRARY_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g -D_REENTRANT)
target_link_libraries(${PROJECT_NAME} -pthread ${SDL_LIBRARIES} engine)

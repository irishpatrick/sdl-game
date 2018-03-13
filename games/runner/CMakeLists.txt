cmake_minimum_required(VERSION 3.0)

project(runner C CXX)

file(GLOB sources src/*.cc)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g -D_REENTRANT)
target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} ${engine_INCLUDE_DIR} ${particles_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${COMPILE_OPTIONS} ${SDL_LIBRARIES} engine particles)

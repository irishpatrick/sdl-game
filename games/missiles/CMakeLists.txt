cmake_minimum_required(VERSION 3.0)

project(missiles C CXX)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL_INCLUDE_DIR} ${engine_INCLUDE_DIRS})
link_directories(${PROJECT_NAME} PUBLIC include ${SDL_LIBRARY_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} ${SDL_LIBRARIES} engine)

cmake_minimum_required(VERSION 3.0)

project(engine C CXX)

file(GLOB sources src/*.cc)
add_library(${PROJECT_NAME} SHARED ${sources})

target_link_libraries(${PROJECT_NAME} -pthread ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL2_INC_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

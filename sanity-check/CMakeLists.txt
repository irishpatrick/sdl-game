cmake_minimum_required(VERSION 3.0)

project(sanity-check C CXX)
set(sources main.cpp)
add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
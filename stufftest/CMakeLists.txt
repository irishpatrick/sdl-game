cmake_minimum_required(VERSION 3.0)

project(stftest C CXX)

file(GLOB sources src/*)
file (GLOB assets assets/*)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE ${stuff_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} stuff stdc++fs)

file(COPY ${assets} DESTINATION ./assets)

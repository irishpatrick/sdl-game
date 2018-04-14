cmake_minimum_required(VERSION 3.0)

project(garden C CXX)

file(GLOB sources src/*.cc)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} ${engine_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} engine)

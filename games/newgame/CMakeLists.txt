cmake_minimum_required(VERSION 3.0)

project(chess C CXX)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${engine_INCLUDE_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} ${MY_LIBS})

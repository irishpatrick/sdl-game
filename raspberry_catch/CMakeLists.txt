cmake_minimum_required(VERSION 3.0)

project(raspberry_catch C CXX)

file (GLOB sources src/*.cpp)
file (GLOB headers include/*.hpp include/*.inl)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_executable(${PROJECT_NAME} ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} ${core_INCLUDE_DIRS} ${ui_INCLUDE_DIRS} ${soundchip_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} core)

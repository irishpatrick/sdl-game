cmake_minimum_required(VERSION 3.0)

project(testbench C CXX)

file(GLOB sources "src/*")

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE include ${INCLUDE_DIR} ${core_INCLUDE_DIRS} ${ui_INCLUDE_DIRS} ${soundchip_INCLUDE_DIRS} ${stuff_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

file(COPY ${assets} DESTINATION ./assets)
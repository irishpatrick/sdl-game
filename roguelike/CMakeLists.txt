cmake_minimum_required(VERSION 3.0)

project(roguelike)

file(GLOB sources src/*.cpp src/*.hpp src/*.inl)
file(GLOB assets assets/*)

link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_DIR})
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCL} ${engine_INCLUDE_DIRS} ${maze_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} engine maze blk)

file(COPY ${assets} DESTINATION ./assets)
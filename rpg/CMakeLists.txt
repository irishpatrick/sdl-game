cmake_minimum_required(VERSION 3.0)

project(rpg C CXX)

file (GLOB_RECURSE sources src/*.cpp)
file (GLOB_RECURSE headers src/*.hpp src/*.inl)
file (GLOB assets assets/*)
file (GLOB_RECURSE scripts scripts/*)

link_directories(${PROJECT_NAME} PRIVATE ${LIBRARY_DIR})
add_executable(${PROJECT_NAME} ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PRIVATE include ${INCLUDE_DIR} ${core_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

file(COPY ${assets} DESTINATION ./assets)
file(COPY ${scripts} DESTINATION ./scripts)

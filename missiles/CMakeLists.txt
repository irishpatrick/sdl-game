cmake_minimum_required(VERSION 3.0)

project(missiles C CXX)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

#[[set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/bin"
)]]

#target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL2_INC_DIR} ${engine_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} -pthread ${SDL2_LIB} ${SDL2_IMAGE_LIB} ${SDL2_TTF_LIB} engine)
#target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g -D_REENTRANT)

target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL2_INC_DIR} ${engine_INCLUDE_DIRS})
link_directories(${PROJECT_NAME} PUBLIC include ${SDL2_LIB_DIR})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g -D_REENTRANT)
target_link_libraries(${PROJECT_NAME} -pthread ${SDL2_LIBS} engine)

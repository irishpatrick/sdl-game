cmake_minimum_required(VERSION 3.0)

project(rpg C CXX)

if (UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
endif (UNIX)

if (MSVC)

endif (MSVC)

file(GLOB sources src/*.cc)
add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}/bin"
)

target_link_libraries(${PROJECT_NAME} -pthread ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} engine)
target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${engine_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g)

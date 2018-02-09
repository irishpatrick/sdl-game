cmake_minimum_required(VERSION 3.0)

project(engine C CXX)

if (UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
endif (UNIX)

if (MSVC)

endif (MSVC)

file(GLOB sources src/*.cc)
add_library(${PROJECT_NAME} SHARED ${sources})

target_link_libraries(${PROJECT_NAME} -pthread ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++11 -Wall -g)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

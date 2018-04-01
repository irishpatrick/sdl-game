cmake_minimum_required(VERSION 3.5)

project(gui C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(cairo REQUIRED cairo)

file(GLOB sources src/*.cc)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} ${cairo_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} ${cairo_CFLAGS_OTHER} -std=c++14 -Wall -fPIC -g -O2 -D_REENTRANT)
target_link_libraries(${PROJECT_NAME} ${LINK_OPTIONS} ${LIBRARIES} ${cairo_LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

cmake_minimum_required(VERSION 3.0)

project(scale C)

file(GLOB sources *.c *.h)

find_package(PkgConfig)

pkg_check_modules(PNG REQUIRED libpng)

set(INCL ${INCL} ${PNG_INCLUDE_DIRS})
set(LIBS ${LIBS} ${PNG_LIBRARIES})

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -g)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCL})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

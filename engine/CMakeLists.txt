cmake_minimum_required(VERSION 3.0)

project(engine)

file(GLOB sources src/*.cpp src/*.hpp src/*.inl)

add_library(${PROJECT_NAME} STATIC ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCL})
if (MSVC)
    #target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS} /DCORE_EXPORTS)
else (MSVC)
    #target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS} -DCORE_EXPORTS)
endif (MSVC)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
set(INCLUDE_DIR ${INCL} ${${PROJECT_NAME}_INCLUDE_DIRS}})

cmake_minimum_required(VERSION 3.0)

project(fork C)

set(sources src/fork.c)

if (MSVC)
    set(fork_COMPILE_OPTIONS /O2 /W3 /MP /D_REENTRANT /c)
    if (DEBUG_SYMBOLS)
        set(fork_COMPILE_OPTIONS ${fork_COMPILE_OPTIONS} /DEBUG /Od)
    endif (DEBUG_SYMBOLS)
else (MSVC)
    set(fork_COMPILE_OPTIONS -O2 -Wall)
    if (DEBUG_SYMBOLS)
        set(fork_COMPILE_OPTIONS ${fork_COMPILE_OPTIONS} -g)
    endif (DEBUG_SYMBOLS)
endif (MSVC)

add_library(${PROJECT_NAME} STATIC ${sources})
target_compile_options(${PROJECT_NAME} PUBLIC ${fork_COMPILE_OPTIONS})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

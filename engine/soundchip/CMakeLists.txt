cmake_minimum_required(VERSION 3.0)

project(soundchip C CXX)

file (GLOB sources src/*.cpp)
file (GLOB headers include/*.hpp)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR} ${OPENAL_SDK}/libs/Win64)
add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} ${OPENAL_SDK}/include)
if (MSVC)
    set(OPENAL_LIBS OpenAL32.lib alut.lib)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} /DSC_EXPORTS)
else (MSVC)
    set(OPENAL_LIBS "")
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -DSC_EXPORTS)
endif (MSVC)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES} ${OPENAL_LIBS})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

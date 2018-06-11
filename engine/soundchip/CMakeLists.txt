cmake_minimum_required(VERSION 3.0)

project(soundchip C CXX)

file (GLOB sources src/*.cpp)
file (GLOB headers include/*.hpp)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR})
if (MSVC)
    set(OPENAL_LIBRARIES OpenAL32.lib alut.lib)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} /DSC_EXPORTS)
else (MSVC)
    set(OPENAL_LIBRARIES "")
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -DSC_EXPORTS)
endif (MSVC)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES} portaudio_static_x64.lib)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

cmake_minimum_required(VERSION 3.0)

project(soundchip C CXX)

if (USE_PKG_CONFIG)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(portaudio REQUIRED portaudio-2.0)
    set(libs portaudio)
elseif (MSVC)
    set(libs portaudio_static_x86.lib)
endif (USE_PKG_CONFIG)

file (GLOB sources src/*.cpp)
file (GLOB headers include/*.hpp)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR} ${portaudio_LIBRARY_DIRS})
add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR} ${portaudio_INCLUDE_DIRS})
if (MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} /DSC_EXPORTS)
else (MSVC)
    set(OPENAL_LIBRARIES "")
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -DSC_EXPORTS)
endif (MSVC)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES} ${libs})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

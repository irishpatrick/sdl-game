cmake_minimum_required(VERSION 3.0)

project(stf C CXX)

file(GLOB sources "src/*")
file(GLOB headers "include/*")

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})

if (MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} /DCORE_EXPORTS)
else (MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -DCORE_EXPORTS)
endif (MSVC)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

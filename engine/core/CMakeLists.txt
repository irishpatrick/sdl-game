cmake_minimum_required(VERSION 3.0)

project(core C CXX)

file (GLOB sources src/*.cpp)
file (GLOB headers include/*.hpp include/*.inl)

link_directories(${PROJECT_NAME} PUBLIC ${LIBRARY_DIR})
add_library(${PROJECT_NAME} STATIC ${sources} ${headers})

target_include_directories(${PROJECT_NAME} PUBLIC include ${INCLUDE_DIR})
if (MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} /DCORE_EXPORTS)
else (MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS} -DCORE_EXPORTS)
endif (MSVC)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

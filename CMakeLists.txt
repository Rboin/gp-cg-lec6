cmake_minimum_required(VERSION 3.6)
project(lec_6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY} ${GLEW_LIBRARY})

set(SOURCE_FILES main.cpp vector.h vector.cpp lecture_6.h lecture_6.cpp)
add_executable(lec_6 ${SOURCE_FILES})

target_link_libraries(lec_6 ${SDL2_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

cmake_minimum_required(VERSION 3.7)
project(lec_6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -lGL")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY} ${GLEW_LIBRARY})

set(SOURCE_FILES main.cpp vector.h vector.cpp lecture_6.h lecture_6.cpp)
add_executable(lec_6 ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "g++")

project(opengl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



add_executable(opengl "window.cpp" "../glad/src/glad.c" "glfw_context.h")
target_include_directories(opengl PRIVATE "../glad/include" "../glad/src/" "../glfw/include/")
target_link_libraries(opengl glfw3 GL X11 pthread Xrandr Xi dl)

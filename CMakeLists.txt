cmake_minimum_required(VERSION 3.10)
#set(CMAKE_CXX_COMPILER "g++")

project(opengl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(glfw3_DIR "C:/Program Files (x86)/GLFW/lib/cmake/glfw3")

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(opengl 
"window.cpp" 
"extern/glad/src/glad.c" 
)
target_include_directories(opengl 
PRIVATE 
"extern/glad/include" 
"extern/glad/src/" 
"extern/"
)
target_link_libraries(opengl 
PUBLIC 
glfw 
OpenGL::GL
)

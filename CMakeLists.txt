cmake_minimum_required(VERSION 3.0)
project(mainProject)

add_executable(cmogl main.cpp)

add_subdirectory(glad/)
add_subdirectory(HeaderFiles/)
target_include_directories(cmogl PRIVATE /usr/include)
target_link_libraries(cmogl PRIVATE glfw3 GL m X11 pthread Xi Xrandr dl glad vbo vao ebo shaderClass)
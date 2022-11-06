cmake_minimum_required(VERSION 3.0)
project(Shaders)

add_library(shaderClass shaderClass.h cpp/shaderClass.cpp)
target_include_directories(shaderClass PUBLIC ../HeaderFiles)

add_library(vbo VBO.h cpp/VBO.cpp)
target_include_directories(vbo PUBLIC ../HeaderFiles)

add_library(vao VAO.h cpp/VAO.cpp)
target_include_directories(vao PUBLIC ../HeaderFiles)

add_library(ebo EBO.h cpp/EBO.cpp)
target_include_directories(ebo PUBLIC ../HeaderFiles)
cmake_minimum_required(VERSION 3.17)
project(ruach_lang)

set(CMAKE_CXX_STANDARD 17)

add_library(ruach_core STATIC src/core/Token.h src/core/Variable.cpp src/core/Variable.h)

add_executable(ruach_interpreter main.cpp)
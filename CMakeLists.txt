cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab3 main.cpp) 
add_executable(lab3 noLeak.cpp)
add_executable(lab3 shar_ptr.cpp)
add_executable(lab3 uniq_ptr.cpp)
add_executable(lab3 weak_ptr.cpp)

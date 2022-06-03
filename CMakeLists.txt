cmake_minimum_required(VERSION 3.5)

project(final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(final main.cpp registry.h employee.h)

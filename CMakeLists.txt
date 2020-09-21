cmake_minimum_required(VERSION 3.10)

project(crsmatrix)

file(GLOB SOURCES "*.cpp")
set(CMAKE_CXX_FLAGS "-Wall -g")

add_executable(crsmatrix ${SOURCES})

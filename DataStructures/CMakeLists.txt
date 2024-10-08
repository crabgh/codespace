cmake_minimum_required(VERSION 3.5)
project(DataStructures)

file(GLOB SRC_FILES
    src/*.cpp
    src/*.hpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
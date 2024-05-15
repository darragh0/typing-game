cmake_minimum_required(VERSION 3.27)
project(typing_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/h)

add_executable(
    typing_game
    src/cpp/config.cpp
    src/cpp/main.cpp
    src/cpp/util.cpp
    src/h/config.h
    src/h/util.h
)

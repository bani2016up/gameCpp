cmake_minimum_required(VERSION 3.29)
project(gameCpp)

set(CMAKE_CXX_STANDARD 23)

add_executable(gameCpp main.cpp
        game.cpp
        eventloop.cpp
        eventloop.h
        field.cpp
        field.hpp
)


cmake_minimum_required(VERSION 3.10)
project(gameCpp)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(gameCpp main.cpp game.cpp field.cpp mpc.cpp)
target_link_libraries(gameCpp ${CURSES_LIBRARIES})

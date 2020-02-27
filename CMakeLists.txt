cmake_minimum_required(VERSION 3.0.0)

project(Gomoku)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-deprecated-declarations")

include_directories(src)
add_executable(${PROJECT_NAME} src/Application.cpp src/Board.cpp src/Stone.cpp src/Gomoku.cpp src/Button.cpp src/GomokuRule.cpp src/GomokuReader.cpp)

add_subdirectory(lib/SFML-2.5.1)
include_directories(include lib/SFML-2.5.1/include)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
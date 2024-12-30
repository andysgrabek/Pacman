cmake_minimum_required(VERSION 3.8)
project(Task8_Pacman)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -pedantic -Werror")

set(SOURCE_FILES main.cpp assets/map.txt PacmanBoard.cpp PacmanBoard.h MovingSprite.cpp MovingSprite.h Ghost.cpp Ghost.h Pacman.cpp Pacman.h pacman_constants.h Counter.cpp Counter.h)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Task8_Pacman ${SOURCE_FILES})

target_link_libraries(Task8_Pacman Qt5::Widgets)

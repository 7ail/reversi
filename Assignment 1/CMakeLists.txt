cmake_minimum_required(VERSION 3.6)
project(Assignment_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        game.c
        game.h
        gameboard.c
        gameboard.h
        player.c
        player.h
        readme.txt
        reversi
        reversi.c
        reversi.h
        scoreboard.c
        scoreboard.h
        shared.h
        utility.c
        utility.h)

add_executable(Assignment_1 ${SOURCE_FILES})
cmake_minimum_required(VERSION 4.2)
project(itwoma C)

set(CMAKE_C_STANDARD 11)

add_executable(itwoma src/main.c
        include/manga.h)

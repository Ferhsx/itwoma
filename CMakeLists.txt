cmake_minimum_required(VERSION 3.28)
project(itwoma C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(itwoma src/main.c
        include/manga.h
        src/manga.c
        src/http_client.c
        src/parser.c
        lib/cJSON/cJSON.c
        )

target_link_libraries(itwoma PRIVATE CURL::libcurl)
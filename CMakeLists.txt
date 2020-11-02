cmake_minimum_required(VERSION 3.18.2)
project(GameLife VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(main ${TARGET_SRC})

target_precompile_headers(main
    PRIVATE "include/stdafx.h"
)

target_include_directories(main
    PRIVATE "./include"
)
cmake_minimum_required(VERSION 3.10)

project(png2n64)

add_executable(png2n64 png2n64.c)

target_link_libraries(png2n64 png)
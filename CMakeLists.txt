cmake_minimum_required(VERSION 3.21)
project(C_test C)

set(CMAKE_C_STANDARD 99)


find_package(SDL2 REQUIRED)
include_directories(C_test ${SDL2_INCLUDE_DIRS})

add_executable(C_test src/main.c src/engine.c src/engine.h)
target_link_libraries(C_test ${SDL2_LIBRARIES})
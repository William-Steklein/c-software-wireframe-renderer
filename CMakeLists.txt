cmake_minimum_required(VERSION 3.16.3)
project(Simple_C_Graphics_Engine)

set(CMAKE_C_FLAGS "-ansi -pedantic")
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

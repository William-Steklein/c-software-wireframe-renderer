cmake_minimum_required(VERSION 3.16.3)
set(PROJECT_NAME Simple_C_Graphics_Engine)
project(${PROJECT_NAME} C)

set(CMAKE_C_STANDARD 99)


find_package(SDL2 REQUIRED)
include_directories(C_test ${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        src/main.c
        src/engine.c
        src/engine.h
        src/DataStructures/Vector2f.h
        src/DataStructures/Figure.h
        src/DataStructures/Plane.h
        src/DataStructures/Line2D.h
        src/DataStructures/Vector3f.h
        src/utils/utils.c
        src/utils/utils.h
        src/DataStructures/Matrix.h
        src/DataStructures/Figure.c
        src/DataStructures/Plane.c
        src/DataStructures/Line2D.c
        src/DataStructures/Vector2f.c
        src/DataStructures/Vector3f.c
        src/DataStructures/Matrix.c
        )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
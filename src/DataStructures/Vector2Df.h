#ifndef SIMPLE_C_GRAPHICS_ENGINE_VECTOR2F_H
#define SIMPLE_C_GRAPHICS_ENGINE_VECTOR2F_H

#include <stdio.h>

typedef struct Vector2Df Vector2Df;
struct Vector2Df {
    float x;
    float y;
};

void vector2df_load(Vector2Df *Vector2f, float x, float y);

void vector2df_print(Vector2Df *vector2f);

#endif //SIMPLE_C_GRAPHICS_ENGINE_VECTOR2F_H

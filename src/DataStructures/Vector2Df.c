#include "Vector2Df.h"

void vector2df_load(Vector2Df *Vector2f, float x, float y) {
    Vector2f->x = x;
    Vector2f->y = y;
}

void vector2df_print(Vector2Df *vector2f) {
    printf("(%f, %f)", vector2f->x, vector2f->y);
}
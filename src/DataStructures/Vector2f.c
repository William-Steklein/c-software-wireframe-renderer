#include "Vector2f.h"

void loadVector2f(Vector2f *Vector2f, float x, float y) {
    Vector2f->x = x;
    Vector2f->y = y;
}

void printVector2f(Vector2f *vector2f) {
    printf("(%f, %f)", vector2f->x, vector2f->y);
}
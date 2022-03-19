#ifndef C_TEST_VECTOR2F_H
#define C_TEST_VECTOR2F_H

#include <stdio.h>

typedef struct Vector2f Vector2f;
struct Vector2f {
    float x;
    float y;
};

void loadVector2f(Vector2f *Vector2f, float x, float y);

void printVector2f(Vector2f *vector2f);

#endif //C_TEST_VECTOR2F_H

#ifndef C_TEST_VECTOR2F_H
#define C_TEST_VECTOR2F_H

typedef struct Vector2f Vector2f;
struct Vector2f {
    float x;
    float y;
};

void loadVector2f(Vector2f *Vector2f, float x, float y) {
    Vector2f->x = x;
    Vector2f->y = y;
}

void printVector2f(Vector2f *vector2f) {
    printf("(%f, %f)", vector2f->x, vector2f->y);
}

// todo: Vector2f math

#endif //C_TEST_VECTOR2F_H

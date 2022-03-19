#ifndef C_TEST_VECTOR3F_H
#define C_TEST_VECTOR3F_H

typedef struct Vector3f Vector3f;
struct Vector3f {
    float x;
    float y;
    float z;
    float h;
};

void loadVector3f(Vector3f *vector3f, float x, float y, float z, float h) {
    vector3f->x = x;
    vector3f->y = y;
    vector3f->z = z;
    vector3f->h = h;
}

void printVector3f(Vector3f *vector3f) {
    printf("(%f, %f, %f, %f)", vector3f->x, vector3f->y, vector3f->z, vector3f->h);
}

// todo: Vector3f math

#endif //C_TEST_VECTOR3F_H

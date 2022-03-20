#ifndef C_TEST_VECTOR3F_H
#define C_TEST_VECTOR3F_H

#include <stdlib.h>
#include <math.h>

typedef struct Vector3f Vector3f;
struct Vector3f {
    float x;
    float y;
    float z;
    float h;
};

void loadVector3f(Vector3f *vector3f, float x, float y, float z, float h);

void printVector3f(Vector3f *vector3f);

Vector3f *addVector3f(Vector3f *v1, Vector3f *v2);

Vector3f *subVector3f(Vector3f *v1, Vector3f *v2);

float lengthVector3f(Vector3f *v);

float vector3fDotVector3f(Vector3f *v1, Vector3f *v2);

Vector3f *normaliseVector3f(Vector3f *v);

Vector3f *vector3fCrossVector3f(Vector3f *v1, Vector3f *v2);

Vector3f *vector3fScalarMult(Vector3f *v, float scalar);

#endif //C_TEST_VECTOR3F_H

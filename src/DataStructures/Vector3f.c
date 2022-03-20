#include "Vector3f.h"

void loadVector3f(Vector3f *vector3f, float x, float y, float z, float h) {
    vector3f->x = x;
    vector3f->y = y;
    vector3f->z = z;
    vector3f->h = h;
}

void printVector3f(Vector3f *vector3f) {
    printf("(%f, %f, %f, %f)", vector3f->x, vector3f->y, vector3f->z, vector3f->h);
}

Vector3f *addVector3f(Vector3f *v1, Vector3f *v2) {
    Vector3f *result = (Vector3f *) malloc(sizeof(Vector3f));
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    return result;
}

Vector3f *subVector3f(Vector3f *v1, Vector3f *v2) {
    Vector3f *result = (Vector3f *) malloc(sizeof(Vector3f));
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    // subtracting two points equals a vector
    if (v1->h && v2->h) result->h = 0;

    return result;
}

float lengthVector3f(Vector3f *v) {
    return sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
}

float vector3fDotVector3f(Vector3f *v1, Vector3f *v2) {
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

Vector3f *normaliseVector3f(Vector3f *v) {
    Vector3f *result = (Vector3f *) malloc(sizeof(Vector3f));
    *result = *v;

    float magnitude = lengthVector3f(v);
    result->x = result->x / magnitude;
    result->y = result->y / magnitude;
    result->z = result->z / magnitude;

    return result;
}

Vector3f *vector3fCrossVector3f(Vector3f *v1, Vector3f *v2) {
    Vector3f *result = (Vector3f *) malloc(sizeof(Vector3f));

    result->x = (v1->y * v2->z) - (v1->z * v2->y);
    result->y = (v1->z * v2->x) - (v1->x * v2->z);
    result->z = (v1->x * v2->y) - (v1->y * v2->x);

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    return result;
}

Vector3f *vector3fScalarMult(Vector3f *v, float scalar) {
    Vector3f *result = (Vector3f *) malloc(sizeof(Vector3f));

    *result = *v;
    result->x *= scalar;
    result->y *= scalar;
    result->z *= scalar;

    return result;
}
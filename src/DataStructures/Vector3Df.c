#include "Vector3Df.h"

void vector3df_load(Vector3Df *vector3f, float x, float y, float z, float h) {
    vector3f->x = x;
    vector3f->y = y;
    vector3f->z = z;
    vector3f->h = h;
}

void vector3df_print(const Vector3Df *vector3f) {
    printf("(%f, %f, %f, %f)", vector3f->x, vector3f->y, vector3f->z, vector3f->h);
}

Vector3Df *vector3df_create_empty() {
    Vector3Df *v = (Vector3Df *) malloc(sizeof(Vector3Df));
    vector3df_load(v, 0, 0, 0, 0);
    return v;
}

Vector3Df *vector3df_add(const Vector3Df *v1, const Vector3Df *v2) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    return result;
}

void vector3df_ref_add(Vector3Df *v1, const Vector3Df *v2) {
    v1->x += v2->x;
    v1->y += v2->y;
    v1->z += v2->z;

    if (v1->h || v2->h) v1->h = 1;
    else v1->h = 0;
}

Vector3Df *vector3df_add_scalar(const Vector3Df *v, float scalar) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));

    *result = *v;
    result->x += scalar;
    result->y += scalar;
    result->z += scalar;

    return result;
}

void vector3df_ref_add_scalar(Vector3Df *v, float scalar) {
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}

Vector3Df *vector3df_subtract(const Vector3Df *v1, const Vector3Df *v2) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    // subtracting two points equals a vector
    if (v1->h && v2->h) result->h = 0;

    return result;
}

void vector3df_ref_subtract(Vector3Df *v1, const Vector3Df *v2) {
    v1->x -= v2->x;
    v1->y -= v2->y;
    v1->z -= v2->z;

    if (v1->h || v2->h) v1->h = 1;
    else v1->h = 0;

    // subtracting two points equals a vector
    if (v1->h && v2->h) v1->h = 0;
}

Vector3Df *vector3df_subtract_scalar(const Vector3Df *v, float scalar) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));

    *result = *v;
    result->x -= scalar;
    result->y -= scalar;
    result->z -= scalar;

    return result;
}

void vector3df_ref_subtract_scalar(Vector3Df *v, float scalar) {
    v->x -= scalar;
    v->y -= scalar;
    v->z -= scalar;
}

Vector3Df *vector3df_multiply_scalar(const Vector3Df *v, float scalar) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));

    *result = *v;
    result->x *= scalar;
    result->y *= scalar;
    result->z *= scalar;

    return result;
}

void vector3df_ref_multiply_scalar(Vector3Df *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

Vector3Df *vector3df_divide_scalar(const Vector3Df *v, float scalar) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));

    *result = *v;
    result->x /= scalar;
    result->y /= scalar;
    result->z /= scalar;

    return result;
}

void vector3df_ref_divide_scalar(Vector3Df *v, float scalar) {
    v->x /= scalar;
    v->y /= scalar;
    v->z /= scalar;
}

float vector3df_length(const Vector3Df *v) {
    return sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
}

float vector3df_v_dot_v(const Vector3Df *v1, const Vector3Df *v2) {
    return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}

Vector3Df *vector3df_normalize(const Vector3Df *v) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));
    *result = *v;

    float magnitude = vector3df_length(v);
    result->x /= magnitude;
    result->y /= magnitude;
    result->z /= magnitude;

    return result;
}

void vector3df_ref_normalize(Vector3Df *v) {
    float magnitude = vector3df_length(v);
    v->x /= magnitude;
    v->y /= magnitude;
    v->z /= magnitude;
}

Vector3Df *vector3df_v_cross_v(const Vector3Df *v1, const Vector3Df *v2) {
    Vector3Df *result = (Vector3Df *) malloc(sizeof(Vector3Df));

    result->x = (v1->y * v2->z) - (v1->z * v2->y);
    result->y = (v1->z * v2->x) - (v1->x * v2->z);
    result->z = (v1->x * v2->y) - (v1->y * v2->x);

    if (v1->h || v2->h) result->h = 1;
    else result->h = 0;

    return result;
}

void vector3df_ref_v_cross_v(Vector3Df *v1, Vector3Df *v2) {
    Vector3Df result;

    result.x = (v1->y * v2->z) - (v1->z * v2->y);
    result.y = (v1->z * v2->x) - (v1->x * v2->z);
    result.z = (v1->x * v2->y) - (v1->y * v2->x);

    if (v1->h || v2->h) result.h = 1;
    else result.h = 0;

    *v1 = result;
}
#ifndef SIMPLE_C_GRAPHICS_ENGINE_VECTOR3F_H
#define SIMPLE_C_GRAPHICS_ENGINE_VECTOR3F_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Vector3Df Vector3Df;
struct Vector3Df {
    float x;
    float y;
    float z;
    float h;
};

void vector3df_load(Vector3Df *vector3f, float x, float y, float z, float h);

void vector3df_print(const Vector3Df *vector3f);

Vector3Df *vector3df_create_empty();

Vector3Df *vector3df_add(const Vector3Df *v1, const Vector3Df *v2);

void vector3df_ref_add(Vector3Df *v1, const Vector3Df *v2);

Vector3Df *vector3df_add_scalar(const Vector3Df *v, float scalar);

void vector3df_ref_add_scalar(Vector3Df *v, float scalar);

Vector3Df *vector3df_subtract(const Vector3Df *v1, const Vector3Df *v2);

void vector3df_ref_subtract(Vector3Df *v1, const Vector3Df *v2);

Vector3Df *vector3df_subtract_scalar(const Vector3Df *v, float scalar);

void vector3df_ref_subtract_scalar(Vector3Df *v, float scalar);

Vector3Df *vector3df_multiply_scalar(const Vector3Df *v, float scalar);

void vector3df_ref_multiply_scalar(Vector3Df *v, float scalar);

Vector3Df *vector3df_divide_scalar(const Vector3Df *v, float scalar);

void vector3df_ref_divide_scalar(Vector3Df *v, float scalar);

float vector3df_length(const Vector3Df *v);

Vector3Df *vector3df_normalize(const Vector3Df *v);

void vector3df_ref_normalize(Vector3Df *v);

float vector3df_v_dot_v(const Vector3Df *v1, const Vector3Df *v2);

Vector3Df *vector3df_v_cross_v(const Vector3Df *v1, const Vector3Df *v2);

void vector3df_ref_v_cross_v(Vector3Df *v1, Vector3Df *v2);

#endif //SIMPLE_C_GRAPHICS_ENGINE_VECTOR3F_H

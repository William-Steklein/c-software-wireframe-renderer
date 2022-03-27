#ifndef SIMPLE_C_GRAPHICS_ENGINE_MATRIX_H
#define SIMPLE_C_GRAPHICS_ENGINE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Vector3Df.h"

typedef struct Matrix Matrix;
struct Matrix {
    int nr_rows;
    int nr_columns;

    float **arr;
};

void matrix_load(Matrix *matrix, int nr_rows, int nr_columns);

void matrix_deep_copy(Matrix *source, Matrix *shallow_copy);

void matrix_print(Matrix *matrix);

void matrix_destroy(Matrix *matrix);

Matrix *matrix_create_unity(int size);

Matrix *matrix_create_scale(float scale);

void matrix_ref_create_scale(Matrix *m, float scale);

Matrix *matrix_create_rotate_x(float angle);

void matrix_ref_create_rotate_x(Matrix *m, float angle);

Matrix *matrix_create_rotate_y(float angle);

void matrix_ref_create_rotate_y(Matrix *m, float angle);

Matrix *matrix_create_rotate_z(float angle);

void matrix_ref_create_rotate_z(Matrix *m, float angle);

Matrix *matrix_create_translate(const Vector3Df *v);

void matrix_ref_create_translate(Matrix *m, const Vector3Df *v);

Matrix *matrix_create_eye_point_trans(const Vector3Df *eye_point);

void matrix_ref_create_eye_point_trans(Matrix *m, const Vector3Df *eye_point);

Matrix *matrix_create_transformation(float scale, float x_rotation, float y_rotation, float z_rotation,
                                     Vector3Df *translation);

void matrix_ref_create_transformation(Matrix *m, float scale, float x_rotation, float y_rotation, float z_rotation,
                                      Vector3Df *translation);

Matrix *matrix_m_dot_m(const Matrix *m1, const Matrix *m2);

void matrix_ref_m_dot_m(Matrix *m1, const Matrix *m2);

Vector3Df *matrix_v_dot_m(Vector3Df *v, Matrix *m);

void matrix_ref_v_dot_m(Vector3Df *v, Matrix *m);

#endif //SIMPLE_C_GRAPHICS_ENGINE_MATRIX_H


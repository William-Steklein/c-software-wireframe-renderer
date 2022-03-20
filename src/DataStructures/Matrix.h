#ifndef C_TEST_MATRIX_H
#define C_TEST_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Vector3f.h"

typedef struct Matrix Matrix;
struct Matrix {
    int nr_rows;
    int nr_columns;

    float **arr;
};

void loadMatrix(Matrix *matrix, int nr_rows, int nr_columns);

void destroyMatrix(Matrix *matrix);

void printMatrix(Matrix *matrix);

Vector3f *vector3fDotMatrix(Vector3f *v, struct Matrix *m);

void vector3frefDotMatrix(Vector3f *v, struct Matrix *m);

Matrix *matrixDotMatrix(Matrix *m1, Matrix *m2);

Matrix *unityM(int size);

Matrix *scaleM(float scale);

Matrix *rotateMX(float angle);

Matrix *rotateMY(float angle);

Matrix *rotateMZ(float angle);

Matrix *translateM(Vector3f *v);

Matrix *eyePointTransM(Vector3f *eye_point);

#endif //C_TEST_MATRIX_H

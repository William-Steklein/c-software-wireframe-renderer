#ifndef C_TEST_MATRIX_H
#define C_TEST_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix Matrix;
struct Matrix {
    int nr_rows;
    int nr_columns;

    float **arr;
};

void loadMatrix(Matrix *matrix, int nr_rows, int nr_columns);

void destroyMatrix(Matrix *matrix);

void printMatrix(Matrix *matrix);

Matrix *createUnityMatrix(int size);

Matrix *matrixDotMatrix(Matrix *m1, Matrix *m2);

#endif //C_TEST_MATRIX_H

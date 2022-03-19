#include "Matrix.h"

void loadMatrix(Matrix *matrix, int nr_rows, int nr_columns) {
    matrix->nr_rows = nr_rows;
    matrix->nr_columns = nr_columns;

    matrix->arr = (float **)malloc(matrix->nr_rows * sizeof(float*));
    int i;
    for (i = 0; i < matrix->nr_rows; i++) {
        matrix->arr[i] = (float *)calloc(matrix->nr_columns, sizeof(float));
    }
}

void destroyMatrix(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->nr_rows; i++) {
        free(matrix->arr[i]);
    }
    free(matrix->arr);
    free(matrix);
}

void printMatrix(Matrix *matrix) {
    int i, j;
    for (i = 0; i < matrix->nr_rows; i++) {
        for (j = 0; j < matrix->nr_columns; j++) {
            printf("%f", matrix->arr[i][j]);
            if (j != matrix->nr_columns - 1)
                printf("\t");
        }
        if (i != matrix->nr_rows - 1)
            printf("\n");
    }
}

Matrix *createUnityMatrix(int size) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    loadMatrix(m, size, size);

    int i;
    for (i = 0; i < size; i++) {
        m->arr[i][i] = 1;
    }

    return m;
}

Matrix *matrixDotMatrix(Matrix *m1, Matrix *m2) {
    // Check if it is possible to multiply
    if (m1->nr_columns != m2->nr_rows)
        return NULL;

    int arr_len = m1->nr_columns;

    Matrix *result = (Matrix *) malloc(sizeof(Matrix));
    loadMatrix(result, m1->nr_rows, m2->nr_columns);

    int m1r, m2c, i;
    float new_value;
    for (m1r = 0; m1r < m1->nr_rows; m1r++) {
        for (m2c = 0; m2c < m2->nr_columns; m2c++) {
            new_value = 0;
            for (i = 0; i < arr_len; i++) {
                new_value += m1->arr[m1r][i] * m2->arr[i][m2c];
            }
            result->arr[m1r][m2c] = new_value;
        }
    }

    return result;
}
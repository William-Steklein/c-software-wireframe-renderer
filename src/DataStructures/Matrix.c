#include "Matrix.h"
#include "../utils/utils.h"

void loadMatrix(Matrix *matrix, int nr_rows, int nr_columns) {
    matrix->nr_rows = nr_rows;
    matrix->nr_columns = nr_columns;

    matrix->arr = (float **) malloc(matrix->nr_rows * sizeof(float *));
    int i;
    for (i = 0; i < matrix->nr_rows; i++) {
        matrix->arr[i] = (float *) calloc(matrix->nr_columns, sizeof(float));
    }
}

void destroyMatrix(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->nr_rows; i++) {
        free(matrix->arr[i]);
    }
    free(matrix->arr);
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

Vector3f *vector3fDotMatrix(Vector3f *v, Matrix *m) {
    // Check if it is possible to multiply
    if (4 != m->nr_rows)
        return NULL;

//    int arr_len = 4;
    Vector3f *result = (Vector3f *) calloc(1, sizeof(Vector3f));

//    int i;
//    for (i = 0; i < arr_len; i++) {
//        result->x += v->x * m->arr[i][0];
//        result->y += v->y * m->arr[i][1];
//        result->z += v->z * m->arr[i][2];
//        result->h += v->h * m->arr[i][3];
//    }

    result->x = (v->x * m->arr[0][0]) + (v->y * m->arr[1][0]) + (v->z * m->arr[2][0]) + (v->h * m->arr[3][0]);
    result->y = (v->x * m->arr[0][1]) + (v->y * m->arr[1][1]) + (v->z * m->arr[2][1]) + (v->h * m->arr[3][1]);
    result->z = (v->x * m->arr[0][2]) + (v->y * m->arr[1][2]) + (v->z * m->arr[2][2]) + (v->h * m->arr[3][2]);
    result->h = (v->x * m->arr[0][3]) + (v->y * m->arr[1][3]) + (v->z * m->arr[2][3]) + (v->h * m->arr[3][3]);

    return result;
}

void vector3frefDotMatrix(Vector3f *v, Matrix *m) {
    // Check if it is possible to multiply
    if (4 != m->nr_rows)
        return;

    Vector3f *temp = vector3fDotMatrix(v, m);

    *v = *temp;
    free(temp);
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

Matrix *unityM(int size) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    loadMatrix(m, size, size);

    int i;
    for (i = 0; i < size; i++) {
        m->arr[i][i] = 1;
    }

    return m;
}

Matrix *scaleM(float scale) {
    Matrix *m = unityM(4);

    m->arr[0][0] = scale;
    m->arr[1][1] = scale;
    m->arr[2][2] = scale;

    return m;
}

Matrix *rotateMX(float angle) {
    Matrix *m = unityM(4);

    m->arr[1][1] = cosf(angle);
    m->arr[1][2] = sinf(angle);
    m->arr[2][1] = -sinf(angle);
    m->arr[2][2] = cosf(angle);

    return m;
}

Matrix *rotateMY(float angle) {
    Matrix *m = unityM(4);

    m->arr[0][0] = cosf(angle);
    m->arr[2][0] = sinf(angle);
    m->arr[0][2] = -sinf(angle);
    m->arr[2][2] = cosf(angle);

    return m;
}

Matrix *rotateMZ(float angle) {
    Matrix *m = unityM(4);

    m->arr[0][0] = cosf(angle);
    m->arr[0][1] = sinf(angle);
    m->arr[1][0] = -sinf(angle);
    m->arr[1][1] = cosf(angle);

    return m;
}

Matrix *translateM(Vector3f *v) {
    Matrix *m = unityM(4);

    m->arr[3][0] = v->x;
    m->arr[3][1] = v->y;
    m->arr[3][2] = v->z;

    return m;
}

Matrix *eyePointTransM(Vector3f *eye_point) {
    Matrix *m = unityM(4);

    float *theta = (float *) malloc(sizeof(float));
    float *phi = (float *) malloc(sizeof(float));
    float *r = (float *) malloc(sizeof(float));
    toPolar(eye_point, theta, phi, r);

    m->arr[0][0] = -sinf(*theta);
    m->arr[0][1] = -cosf(*theta) * cosf(*phi);
    m->arr[0][2] = cosf(*theta) * sinf(*phi);

    m->arr[1][0] = cosf(*theta);
    m->arr[1][1] = -sinf(*theta) * cosf(*phi);
    m->arr[1][2] = sinf(*theta) * sinf(*phi);

    m->arr[2][1] = sinf(*phi);
    m->arr[2][2] = cosf(*phi);

    m->arr[3][2] = -*r;

    free(theta);
    free(phi);
    free(r);

    return m;
}
#include "Matrix.h"
#include "../utils/utils.h"

void matrix_load(Matrix *matrix, int nr_rows, int nr_columns) {
    matrix->nr_rows = nr_rows;
    matrix->nr_columns = nr_columns;

    matrix->arr = (float **) malloc(matrix->nr_rows * sizeof(float *));
    for (int i = 0; i < matrix->nr_rows; i++) {
        matrix->arr[i] = (float *) calloc(matrix->nr_columns, sizeof(float));
    }
}

void matrix_deep_copy(Matrix *source, Matrix *shallow_copy) {
    shallow_copy->nr_rows = source->nr_rows;
    shallow_copy->nr_columns = source->nr_columns;

    shallow_copy->arr = (float **) malloc(source->nr_rows * sizeof(float *));
    for (int i = 0; i < source->nr_rows; i++) {
        shallow_copy->arr[i] = (float *) malloc(source->nr_columns * sizeof(float));
        memcpy(shallow_copy->arr + i, source->arr + i, source->nr_columns * sizeof(float));
    }
}

void matrix_destroy(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->nr_rows; i++) {
        free(matrix->arr[i]);
    }
    free(matrix->arr);
}

void matrix_print(Matrix *matrix) {
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

void matrix_clear(Matrix *matrix) {
    int i, j;
    for (i = 0; i < matrix->nr_rows; i++) {
        for (j = 0; j < matrix->nr_columns; j++) {
            if (i == j) {
                matrix->arr[i][j] = 1;
            } else {
                matrix->arr[i][j] = 0;
            }
        }
    }
}

Vector3Df *matrix_v_dot_m(Vector3Df *v, Matrix *m) {
    // Check if it is possible to multiply
    if (4 != m->nr_rows)
        return NULL;

    Vector3Df *result = (Vector3Df *) calloc(1, sizeof(Vector3Df));

    result->x = (v->x * m->arr[0][0]) + (v->y * m->arr[1][0]) + (v->z * m->arr[2][0]) + (v->h * m->arr[3][0]);
    result->y = (v->x * m->arr[0][1]) + (v->y * m->arr[1][1]) + (v->z * m->arr[2][1]) + (v->h * m->arr[3][1]);
    result->z = (v->x * m->arr[0][2]) + (v->y * m->arr[1][2]) + (v->z * m->arr[2][2]) + (v->h * m->arr[3][2]);
    result->h = (v->x * m->arr[0][3]) + (v->y * m->arr[1][3]) + (v->z * m->arr[2][3]) + (v->h * m->arr[3][3]);

    return result;
}

void matrix_ref_v_dot_m(Vector3Df *v, Matrix *m) {
    // Check if it is possible to multiply
    if (4 != m->nr_rows)
        return;

    Vector3Df *temp = matrix_v_dot_m(v, m);

    *v = *temp;
    free(temp);
}

Matrix *matrix_m_dot_m(const Matrix *m1, const Matrix *m2) {
    // Check if it is possible to multiply
    if (m1->nr_columns != m2->nr_rows)
        return NULL;

    int arr_len = m1->nr_columns;

    Matrix *result = (Matrix *) malloc(sizeof(Matrix));
    matrix_load(result, m1->nr_rows, m2->nr_columns);

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

void matrix_ref_m_dot_m(Matrix *m1, const Matrix *m2) {
    // Check if it is possible to multiply
    if (m1->nr_columns != m2->nr_rows)
        return;

    Matrix *result = matrix_m_dot_m(m1, m2);

    matrix_destroy(m1);
    *m1 = *result;
    free(result);
}

Matrix *matrix_create_unity(int size) {
    Matrix *m = (Matrix *) malloc(sizeof(Matrix));
    matrix_load(m, size, size);

    int i;
    for (i = 0; i < size; i++) {
        m->arr[i][i] = 1;
    }

    return m;
}

Matrix *matrix_create_scale(float scale) {
    Matrix *m = matrix_create_unity(4);

    matrix_ref_create_scale(m, scale);

    return m;
}

void matrix_ref_create_scale(Matrix *m, float scale) {
    matrix_clear(m);

    m->arr[0][0] = scale;
    m->arr[1][1] = scale;
    m->arr[2][2] = scale;
}

Matrix *matrix_create_rotate_x(float angle) {
    Matrix *m = matrix_create_unity(4);

    matrix_ref_create_rotate_x(m, angle);

    return m;
}

void matrix_ref_create_rotate_x(Matrix *m, float angle) {
    matrix_clear(m);

    m->arr[1][1] = cosf(angle);
    m->arr[1][2] = sinf(angle);
    m->arr[2][1] = -sinf(angle);
    m->arr[2][2] = cosf(angle);
}

Matrix *matrix_create_rotate_y(float angle) {
    Matrix *m = matrix_create_unity(4);

    matrix_ref_create_rotate_y(m, angle);

    return m;
}

void matrix_ref_create_rotate_y(Matrix *m, float angle) {
    matrix_clear(m);

    m->arr[0][0] = cosf(angle);
    m->arr[2][0] = sinf(angle);
    m->arr[0][2] = -sinf(angle);
    m->arr[2][2] = cosf(angle);
}

Matrix *matrix_create_rotate_z(float angle) {
    Matrix *m = matrix_create_unity(4);

    matrix_ref_create_rotate_z(m, angle);

    return m;
}

void matrix_ref_create_rotate_z(Matrix *m, float angle) {
    matrix_clear(m);

    m->arr[0][0] = cosf(angle);
    m->arr[0][1] = sinf(angle);
    m->arr[1][0] = -sinf(angle);
    m->arr[1][1] = cosf(angle);
}

Matrix *matrix_create_translate(const Vector3Df *v) {
    Matrix *m = matrix_create_unity(4);

    matrix_ref_create_translate(m, v);

    return m;
}

void matrix_ref_create_translate(Matrix *m, const Vector3Df *v) {
    matrix_clear(m);

    m->arr[3][0] = v->x;
    m->arr[3][1] = v->y;
    m->arr[3][2] = v->z;
}

Matrix *matrix_create_eye_point_trans(const Vector3Df *eye_point) {
    Matrix *m = matrix_create_unity(4);

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

Matrix *matrix_create_transformation(float scale, float x_rotation, float y_rotation, float z_rotation,
                                     Vector3Df *translation) {
    Matrix *result = matrix_create_scale(scale);
    Matrix *temp = matrix_create_rotate_x(x_rotation);

    matrix_ref_m_dot_m(result, temp);

    matrix_ref_create_rotate_y(temp, y_rotation);
    matrix_ref_m_dot_m(result, temp);

    matrix_ref_create_rotate_z(temp, z_rotation);
    matrix_ref_m_dot_m(result, temp);

    matrix_ref_create_translate(temp, translation);
    matrix_ref_m_dot_m(result, temp);

    matrix_destroy(temp);
    free(temp);

    return result;
}

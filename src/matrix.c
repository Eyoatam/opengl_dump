#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define SIZE 4 // size of matrix
#define PI 3.141592654

void matrix_identity(float *matrix) {
    for (int rows = 0; rows < SIZE; rows++) {
        for (int cols = 0; cols < SIZE; cols++) {
            matrix[rows * SIZE + cols] = (rows == cols) ? 1.0f : 0.0f;
        }
    }
}

void matrix_transpose(float *matrix) {
    for (int rows = 0; rows < SIZE; rows++) {
        for (int cols = rows + 1; cols < SIZE; cols++) {
            int index = rows * SIZE + cols;
            int transpose_index = cols * SIZE + rows;
            float tmp = matrix[index];
            matrix[index] = matrix[transpose_index];
            matrix[transpose_index] = tmp;
        }
    }
}

void matrix_mul(float *out, float *a, float *b) {
    for (int rows = 0; rows < SIZE; rows++) {
        for (int cols = 0; cols < SIZE; cols++) {
            float value = 0.0f;
            for (int i = 0; i < SIZE; i++) {
                value += a[rows * SIZE + i] * b[i * SIZE + cols];
            }
            out[rows * SIZE + cols] = value;
        }
    }
}

void matrix_vec_mul(float *out, float *mat, float *vec) {
    for (int rows = 0; rows < SIZE; rows++) {
        float value = 0.0f;
        for (int cols = 0; cols < SIZE; cols++) {
            value += mat[rows * SIZE + cols] * vec[cols];
        }
        out[rows] = value;
    }
}

void matrix_copy(float *dest, float *src) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        dest[i] = src[i];
    }
}

void translate(float *matrix, float *tr_vec) {
    float translation_matrix[SIZE * SIZE] = {};
    matrix_identity(translation_matrix);
    // column major ordering
    translation_matrix[12] = tr_vec[0];
    translation_matrix[13] = tr_vec[1];
    translation_matrix[14] = tr_vec[2];

    float out_matrix[SIZE * SIZE];
    matrix_mul(out_matrix, matrix, translation_matrix);
    matrix_copy(matrix, out_matrix);
}

void scale(float *matrix, float *factor) {
    float scale_matrix[SIZE * SIZE] = {};
    matrix_identity(scale_matrix);

    scale_matrix[0] = factor[0];
    scale_matrix[5] = factor[1];
    scale_matrix[9] = factor[2];

    float out_matrix[SIZE * SIZE];
    matrix_mul(out_matrix, matrix, scale_matrix);
    matrix_copy(matrix, out_matrix);
}

float radians(float degree) { return (degree * PI) / 180; }

void rotate(float *matrix, float angle, float *axis) {
    float rotation_matrix[SIZE * SIZE] = {};

    // store repeated variables
    float c = cosf(angle);
    float s = sinf(angle);
    float i = 1 - c;

    // axes
    float x = axis[0];
    float y = axis[1];
    float z = axis[2];

    // column-major ordering
    rotation_matrix[0] = c + x * x * i;
    rotation_matrix[1] = x * y * i - z * s;
    rotation_matrix[2] = x * z * i + y * s;
    rotation_matrix[4] = y * x * i + z * s;
    rotation_matrix[5] = c + y * y * i;
    rotation_matrix[6] = y * z * i - x * s;
    rotation_matrix[8] = z * x * i - y * s;
    rotation_matrix[9] = z * y * i + x * s;
    rotation_matrix[10] = c + z * z * i;
    rotation_matrix[15] = 1;

    float out_matrix[SIZE * SIZE];
    matrix_mul(out_matrix, matrix, rotation_matrix);
    matrix_copy(matrix, out_matrix);
}

void make_frustum(float *matrix, float fov, float aspect_ratio, float near,
                  float far) {
    float tangent = tan(fov / 2);
    float top = near * tangent;
    float right = top * aspect_ratio;

    matrix[0] = near / right;
    matrix[5] = near / top;
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1;
    matrix[14] = -(2 * far * near) / (far - near);
    matrix[15] = 0;
}

void matrix_ortho(float *matrix, float left, float right, float bottom,
                  float top, float near, float far) {
    matrix[0] = 2 / (right - left);
    matrix[5] = 2 / (top - bottom);
    matrix[10] = -2 / (far - near);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(far + near) / (far - near);
    matrix[15] = 1;
}

void print_matrix(float *matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f ", matrix[i * size + j]);
        }
        printf("\n");
    }
}

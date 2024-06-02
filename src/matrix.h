#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

void matrix_mul(float* out, float* a, float* b);
void matrix_vec_mul(float* out, float* mat, float* vec);
void matrix_identity(float* matrix);
void matrix_transpose(float* matrix);
void translate(float* matrix, float* tr_vec);
void scale(float* matrix, float* factor);
void rotate(float* matrix, float angle, float* axes);
void make_frustum(float* matrix, float fov, float aspect_ratio, float near, float far);
void matrix_ortho(float* matrix, float left, float right, float bottom, float top, float near, float far);
// utils
float radians(float angle);
void print_matrix(float* matrix, int size);
#endif

#ifndef MATRIX_H
#define MATRIX_H

#include "func.h"
#include "element.h"
#include "array.h"

struct TypeMatrix;

typedef struct {
    Array* array;
    int row, col;
    const struct TypeMatrix* type_matrix;
} Matrix;

typedef struct TypeMatrix {
    Matrix* (*scan)(const char* str);
    char* (*print)(Matrix*);
    Matrix* (*sum)(Matrix* matrix1, Matrix* matrix2);
    Matrix* (*multiply)(Matrix* matrix1, Matrix* matrix2);
    Matrix* (*transponate)(Matrix* matrix);
    Matrix* (*linear_combination)(Matrix* matrix, int from_row, int to_row, Element* coeff);
    Matrix* (*create)(Array* array, int row, int col);
    int (*destroy)(Matrix* matrix);
    int (*get_rows)(Matrix* matrix);
    int (*get_cols)(Matrix* matrix);
    Array* (*get_array)(Matrix* matrix);

} TypeMatrix;

Matrix* create_matrix(Array* array, int row, int col);
Matrix* fill_matrix_from_string(const char* input);
char* print_matrix(Matrix* matrix);
Matrix* sum_matrix(Matrix* matrix1, Matrix* matrix2);
int destroy_matrix(Matrix* matrix);
Matrix* mult_matrix(Matrix* matrix1, Matrix* matrix2);
Matrix* transponate_matrix(Matrix* matrix);
Matrix* matrix_linear_combination(Matrix* matrix, int from_row, int to_row, Element* coeff);
int get_rows(Matrix* matrix);
int get_cols(Matrix* matrix);
Array* get_array(Matrix* matrix);
Matrix* string_to_matrix(const char* str);

#endif
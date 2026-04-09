#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "matrix.h"
#include "element.h"
#include "array.h"

 TypeMatrix MyMatrix = {
    .scan = fill_matrix_from_string,
    .print = print_matrix,
    .sum = sum_matrix,
    .multiply = mult_matrix,
    .transponate = transponate_matrix,
    .linear_combination = matrix_linear_combination,
    .create = create_matrix,
    .destroy = destroy_matrix
};

Matrix* create_matrix(Array* array, int row, int col) {
    if (array == NULL || row <= 0 || col <= 0) return NULL;
    Matrix *matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) return NULL;
    matrix->col = col;
    matrix->row = row;
    matrix->array = array;
    return matrix;
}

int destroy_matrix(Matrix* matrix) {
    if (matrix == NULL) return 0;
    if (matrix->array != NULL) {
        destroy_array(matrix->array);
        matrix->array = NULL;  
    }
    free(matrix);
    return 1;
}

int get_rows(Matrix* matrix) {
    if (matrix == NULL) return 0;
    return matrix->row;
}

int get_cols(Matrix* matrix) {
    if (matrix == NULL) return 0;
    return matrix->col;
}

char* print_matrix(Matrix* matrix) {
    if (matrix == NULL) return NULL;
    char* buffer = malloc(8192);
    if (buffer == NULL) return NULL;
    char* ptr = buffer;
    char* end = buffer + 8192;
    ptr += snprintf(ptr, end - ptr, "\n");
    for (int i = 0; i < get_rows(matrix); i++) {
        ptr += snprintf(ptr, end - ptr, "│");
        for (int j = 0; j < get_cols(matrix); j++) {
            if (j != 0) {
                ptr += snprintf(ptr, end - ptr, " ");
            }
            int index = i * get_cols(matrix) + j;
             Element* elem = get_element_by_index(get_array(matrix), index);
            char* elem_str = print(elem);
            if (elem_str) {
                ptr += snprintf(ptr, end - ptr, "%s", elem_str);
                free(elem_str);
            }
        }
        ptr += snprintf(ptr, end - ptr, "│\n");
    }
    return buffer;
}

Matrix* fill_matrix_from_string( char* input) {
    if (input == NULL) return NULL;
    int row, col, type;
    int offset = 0, consumed = 0;
    char* endptr;
    if (sscanf(input, "%d %d %d%n", &row, &col, &type, &consumed) != 3) {
        errno = EINVAL;
        perror("fill_matrix_from_string (header format)");
        return NULL;
    }
    offset = consumed;
    if (row <= 0 || col <= 0 || (type != 1 && type != 2)) {
        errno = EINVAL;
        perror("fill_matrix_from_string (params)");
        return NULL;
    }
    Array* array = create_array_size_element(row * col);
    if (!array) return NULL; 
    TypeElement* elem_type = (type == 1) ? &IntType : &FloatType;
    for (int i = 0; i < row * col; i++) {
        set_element_by_index(array, i, elem_type->create());
    }
    Matrix* matrix = create_matrix(array, row, col);
    if (!matrix) {
        destroy_array(array); 
        return NULL;
    }
    for (int i = 0; i < row * col; i++) {
        while (input[offset] == ' ' || input[offset] == '\n' || input[offset] == '\t') {
            offset++;
        }
        if (type == 1) {
            long val = strtol(input + offset, &endptr, 10);
            if (endptr == input + offset) {
                errno = EINVAL;
                perror("fill_matrix_from_string (int parse)");
                destroy_matrix(matrix);
                return NULL;
            }
            set_int_number(get_element_by_index(get_array(matrix), i), (int)val);
            offset = endptr - input; 
        } else {
            float val = strtof(input + offset, &endptr);
            if (endptr == input + offset) {
                errno = EINVAL;
                perror("fill_matrix_from_string (float parse)");
                destroy_matrix(matrix); 
                return NULL;
            }
            set_float_number(get_element_by_index(get_array(matrix), i), val);
            offset = endptr - input;
        }
    }
    return matrix;
}

Matrix* sum_matrix(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1 == NULL || matrix2 == NULL) return NULL;
    if (get_cols(matrix1) != get_cols(matrix2) || get_rows(matrix1) != get_rows(matrix2)) return NULL;
     TypeElement* type = get_array_type(get_array(matrix1));
    if (type == NULL || type != get_array_type(get_array(matrix2))) return NULL;

    Array* array = create_array_size_element(get_rows(matrix1) * get_cols(matrix1));
    if (!array) return NULL;
    for (int i = 0; i < get_rows(matrix1) * get_cols(matrix1); i++) {
        set_element_by_index(array, i, type->create_null());
    }
    Matrix* matrix = create_matrix(array, get_rows(matrix1), get_cols(matrix1));
    if (!matrix) {
        destroy_array(array);
        return NULL;
    }
    for (int i = 0; i < get_rows(matrix1); i++) {
        for (int j = 0; j < get_cols(matrix1); j++) {
            int index = i * get_cols(matrix1) + j;
            Element* res = sum(get_element_by_index(get_array(matrix1), index), get_element_by_index(get_array(matrix2), index));
            if (res) set_element_by_index(get_array(matrix), index, res);
        }
    }
    return matrix;
}

Matrix* mult_matrix(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1 == NULL || matrix2 == NULL) return NULL;
    if (get_cols(matrix1) != get_rows(matrix2)) return NULL;
     TypeElement* type = get_array_type(get_array(matrix1));
    if (type == NULL || type != get_array_type(get_array(matrix2))) return NULL;

    Array* array = create_array_size_element(get_rows(matrix1) * get_cols(matrix2));
    if (!array) return NULL;
    for (int i = 0; i < get_rows(matrix1) * get_cols(matrix2); i++) {
        set_element_by_index(array, i, type->create_null());
    }
    Matrix* matrix = create_matrix(array, get_rows(matrix1), get_cols(matrix2));
    if (!matrix) {
        destroy_array(array);
        return NULL;
    }
    for (int i = 0; i < get_rows(matrix1); i++) {
        for (int j = 0; j < get_cols(matrix2); j++) {
            int index = i * get_cols(matrix2) + j;
            for (int k = 0; k < get_cols(matrix1); k++) {
                int index_left = i * get_cols(matrix1) + k;
                int index_right = k * get_cols(matrix2) + j;
                Element* prod = multiply(get_element_by_index(get_array(matrix1), index_left), get_element_by_index(get_array(matrix2), index_right));
                if (prod == NULL) continue;
                Element* old = get_element_by_index(get_array(matrix), index);
                Element* res = sum(old, prod);
                if (res) set_element_by_index(get_array(matrix), index, res);
                destroy_elem(prod);
            } 
        }
    }
    return matrix;
}

Matrix* transponate_matrix(Matrix* matrix) {
    if (matrix == NULL) return NULL;
    int rows = get_rows(matrix);
    int cols = get_cols(matrix);
     TypeElement* type = get_array_type(get_array(matrix));
    if (type == NULL) return NULL;
    
    Array* array = create_array_size_element(rows * cols);
    if (!array) return NULL;
    for (int i = 0; i < rows * cols; i++) {
        set_element_by_index(array, i, type->create());
    }
    Matrix* new_matrix = create_matrix(array, cols, rows);
    if (!new_matrix) {
        destroy_array(array);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int src_index = i * cols + j;
            int dst_index = j * rows + i;
            Element* src = get_element_by_index(get_array(matrix), src_index);
            Element* dst = get_element_by_index(get_array(new_matrix), dst_index);
            if (src && dst && src->number && dst->number) {
                memcpy(dst->number, src->number, src->size);
            }
        }
    }
    return new_matrix;
}

Matrix* matrix_linear_combination(Matrix* matrix, int from_row, int to_row, Element* coeff) {
    if (matrix == NULL || coeff == NULL) return NULL;
     TypeElement* type = get_array_type(get_array(matrix));
    if (type == NULL || type != coeff->type_element) return NULL;
    
    Array* array = create_array_size_element(get_cols(matrix) * get_rows(matrix));
    if (!array) return NULL;
    for (int i = 0; i < get_cols(matrix) * get_rows(matrix); i++) {
        set_element_by_index(array, i, type->create());
    }
    Matrix* new_matrix = create_matrix(array, get_rows(matrix), get_cols(matrix));
    if (!new_matrix) {
        destroy_array(array);
        return NULL;
    }
    for (int i = 0; i < get_rows(matrix); i++) {
        for (int j = 0; j < get_cols(matrix); j++) {
            int index = i * get_cols(matrix) + j;
            Element* src = get_element_by_index(get_array(matrix), index);
            Element* dst = get_element_by_index(get_array(new_matrix), index);
            if (src && dst && src->number && dst->number) {
                memcpy(dst->number, src->number, src->size);
            }
        }
    }
    to_row--; from_row--;
    int index_to = to_row * get_cols(new_matrix);
    int index_from = from_row * get_cols(new_matrix);
    for (int j = 0; j < get_cols(new_matrix); j++, index_to++, index_from++) {
        Element* from_elem = get_element_by_index(get_array(new_matrix), index_from);
        Element* to_elem = get_element_by_index(get_array(new_matrix), index_to);
        if (from_elem && to_elem) {
            Element* scaled = multiply(coeff, from_elem);
            if (scaled) {
                Element* result = sum(to_elem, scaled);
                if (result) set_element_by_index(get_array(new_matrix), index_to, result);
                destroy_elem(scaled);
            }
        }
    }
    return new_matrix;
}

Array* get_array(Matrix* matrix) {
    if (matrix == NULL) return NULL;
    return matrix->array;
}

Matrix* string_to_matrix( char* str) {
    return fill_matrix_from_string(str);
}
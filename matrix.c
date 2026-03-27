#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "element.h"
#include "array.h"

const TypeMatrix MyMatrix = {
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
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->array = array;

    return matrix;
}

// int destroy_matrix(Matrix* matrix) {
//     return 1;
// }

int destroy_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return 0;
    }

    if (matrix->array != NULL) {
        destroy_array(matrix->array);
        matrix->array = NULL;  
    }
    free(matrix);

    return 1;
}


int get_rows(Matrix* matrix) {
    return matrix->row;
}
int get_cols(Matrix* matrix) {
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
            const Element* elem = get_element_by_index(get_array(matrix), index);
            
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

Matrix* fill_matrix_from_string(const char* input) {
    int row, col, type;
    int offset = 0, consumed = 0;
    char* endptr;

    if (sscanf(input, "%d %d %d%n", &row, &col, &type, &consumed) != 3) {
        printf("Ошибка: неверный формат заголовка.\n");
        return NULL;
    }
    offset = consumed;

    if (row <= 0 || col <= 0 || (type != 1 && type != 2)) {
        printf("Ошибка: некорректные параметры.\n");
        return NULL;
    }

    Array* array = create_array_size_element(row * col);
    if (!array) return NULL; 

    for (int i = 0; i < row * col; i++) {
        set_element_by_index(array, i, ((type == 1) ? create("int") : create("float")));
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
                printf("Ошибка: ожидалось число (int) на позиции %d.\n", i);
                destroy_matrix(matrix);
                return NULL;
            }
            set_int_number(get_element_by_index(get_array(matrix), i), (int)val);
            offset = endptr - input; 
        } else {
            float val = strtof(input + offset, &endptr);
            if (endptr == input + offset) {
                printf("Ошибка: ожидалось число (float) на позиции %d.\n", i);
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
    if ((get_cols(matrix1) != get_cols(matrix2)) || (get_rows(matrix1) != get_rows(matrix2)) || (get_array_type(get_array(matrix1)) != get_array_type(get_array(matrix2)))) {
        return NULL;
    }

    Array* array = create_array_size_element(get_rows(matrix1) * get_cols(matrix1));

    for (int i = 0; i < get_rows(matrix1) * get_cols(matrix1); i++) {
        if (get_array_type(get_array(matrix1)) == TYPE_INT) {
            set_element_by_index(array, i, create_null("int"));
        }
        else if (get_array_type(get_array(matrix1)) == TYPE_FLOAT) {
            set_element_by_index(array, i, create_null("float"));
        }
        else {
            return NULL;
        }
    }

    Matrix* matrix = create_matrix(array, get_rows(matrix1), get_cols(matrix1));

    for (int i = 0; i < get_rows(matrix1); i++) {
        for (int j = 0; j < get_cols(matrix1); j++) {
            int index = i * get_cols(matrix) + j;
            set_element_by_index(get_array(matrix), index, sum(get_element_by_index(get_array(matrix1), index), get_element_by_index(get_array(matrix2), index)));
        }
    }
    return matrix;
}


Matrix* mult_matrix(Matrix* matrix1, Matrix* matrix2) {
    if (get_cols(matrix1) != get_rows(matrix2) || (get_array_type(get_array(matrix1)) != get_array_type(get_array(matrix2)))) {
        return NULL;
    }

    Array* array = create_array_size_element(get_rows(matrix1) * get_cols(matrix2));

    for (int i = 0; i < get_rows(matrix1) * get_cols(matrix2); i++) {
        if (get_array_type(get_array(matrix1)) == TYPE_INT) {
            set_element_by_index(array, i, create_null("int"));
        }
        else if (get_array_type(get_array(matrix1)) == TYPE_FLOAT) {
            set_element_by_index(array, i, create_null("float"));
        }
        else {
            return NULL;
        }
    }
    
    Matrix* matrix = create_matrix(array, get_rows(matrix1), get_cols(matrix2));

    for (int i = 0; i < get_rows(matrix1); i++) {
        for (int j = 0; j < get_cols(matrix2); j++) {
            int index = i * get_cols(matrix) + j;
            for (int k = 0; k < get_cols(matrix1); k++) {
                int index_left = i * get_cols(matrix1) + k;
                int index_right = k * get_cols(matrix2) + j;

                Element elem = *multiply(get_element_by_index(get_array(matrix1), index_left), get_element_by_index(get_array(matrix2), index_right));
                Element old_elem = *get_element_by_index(get_array(matrix), index);
                set_element_by_index(get_array(matrix), index, sum(&elem, &old_elem));
            } 
        }
    }

    return matrix;
}

Matrix* transponate_matrix(Matrix* matrix) {
    if (matrix == NULL) return NULL;

    int rows = get_rows(matrix);
    int cols = get_cols(matrix);
    
    Array* array = create_array_size_element(rows * cols);
    if (!array) return NULL;

    for (int i = 0; i < rows * cols; i++) {
        if (get_array_type(get_array(matrix)) == TYPE_INT) {
            set_element_by_index(array, i, create("int"));
        }
        else if (get_array_type(get_array(matrix)) == TYPE_FLOAT) {
            set_element_by_index(array, i, create("float"));
        }
        else {
            destroy_array(array);
            return NULL;
        }
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
            
            if (src->type == TYPE_INT) {
                *(int*)dst->number = *(int*)src->number;
            } else {
                *(float*)dst->number = *(float*)src->number;
            }
        }
    }

    return new_matrix;
}

Matrix* matrix_linear_combination(Matrix* matrix, int from_row, int to_row, Element* coeff) {
    Array* array = create_array_size_element(get_cols(matrix) * get_cols(matrix));

    for (int i = 0; i < get_cols(matrix) * get_rows(matrix); i++) {
        if (get_array_type(get_array(matrix)) == TYPE_INT) {
            set_element_by_index(array, i, create("int"));
        }
        else if (get_array_type(get_array(matrix)) == TYPE_FLOAT) {
            set_element_by_index(array, i, create("float"));
        }
        else {
            return NULL;
        }
    }
    
    Matrix* new_matrix = create_matrix(array, get_rows(matrix), get_cols(matrix));

    to_row--, from_row--;

    
    for (int i = 0; i < get_rows(matrix); i++) {
        for (int j = 0; j < get_cols(matrix); j++) {
            int index = i * get_cols(matrix) + j;
            set_element_by_index(get_array(new_matrix), index, get_element_by_index(get_array(matrix), index));
        }
    }

    int index_to = to_row * get_rows(new_matrix), index_from = from_row * get_rows(new_matrix);
    for (int j = 0; j < get_cols(new_matrix); j++, index_to++, index_from++) {
        Element from_elem = *multiply(coeff, get_element_by_index(get_array(new_matrix), index_from));
        Element to_elem = *get_element_by_index(get_array(new_matrix), index_to);
        set_element_by_index(get_array(new_matrix), index_to, sum(&from_elem, &to_elem));
    }
    return new_matrix;
}

Array* get_array(Matrix* matrix) {
    return matrix->array;
}

Matrix* string_to_matrix(const char* str) {
    return fill_matrix_from_string(str);
}

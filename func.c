#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "array.h"
#include "matrix.h"

#define WIDTH 6

int max(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2) {
    return (num1 < num2) ? num1 : num2;
}

void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

int read_int( char* input, int* output) {
    if (input == NULL || output == NULL) {
        return 0;
    }
    printf("%s", input);
    if (scanf("%d", output) != 1) {
        clear_buffer();
        return 0;
    }
    clear_buffer();
    return 1;
}

char* get_string_from_user() {
    static char buffer[1024];
    char line[256];
    buffer[0] = '\0';
    size_t total_len = 0;
    printf("Вводите числа (пустая строка для завершения):\n");
    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len-1] == '\n') {
            line[line_len-1] = '\0';
            line_len--;
        }
        if (line_len == 0) {
            if (total_len > 0) {
                break;
            } else {
                continue;
            }
        }
        if (total_len > 0 && total_len < sizeof(buffer) - 1) {
            buffer[total_len++] = ' ';
            buffer[total_len] = '\0';
        }
        if (total_len + line_len < sizeof(buffer) - 1) {
            strcpy(buffer + total_len, line);
            total_len += line_len;
        } else {
            errno = ENOBUFS;
            perror("get_string_from_user (buffer overflow)");
            break;
        }
    }
    return (total_len > 0) ? buffer : NULL;
}

 char* format_matrix(int rows, int cols,  TypeElement* type,  char* matrix_data) {
    if (matrix_data == NULL) {
        return NULL;
    }
    size_t header_size = 50;
    size_t data_size = strlen(matrix_data);
    size_t total_size = header_size + data_size + 2;
    char* result = (char*)malloc(total_size);
    if (result == NULL) {
        return NULL;
    }
    int type_id = (type == &IntType) ? 1 : 2;
    sprintf(result, "%d %d %d\n%s", rows, cols, type_id, matrix_data);
    return ( char*)result;
}

Matrix* fill_matrix_w_predicted_value( TypeElement* type, int expected_rows, int expected_cols) {
    int row, col;
    printf("\n========================================\n");
    printf("         ВВОД НОВОЙ МАТРИЦЫ             \n");
    printf("========================================\n");
    printf("Ожидаемый размер: %d x %d\n", expected_rows, expected_cols);

    if (!read_int("Количество строк: ", &row) || row <= 0) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (rows)");
        return NULL;
    }
    if (!read_int("Количество столбцов: ", &col) || col <= 0) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (cols)");
        return NULL;
    }
    if (row != expected_rows || col != expected_cols) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (size mismatch)");
        return NULL;
    }
    if (type != &IntType && type != &FloatType) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (type)");
        return NULL;
    }
    printf("========================================\n");
    char* data = get_string_from_user();
    if (data == NULL) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (data)");
        return NULL;
    }
     char* formatted = format_matrix(row, col, type, data);
    if (formatted == NULL) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (format)");
        return NULL;
    }
    Matrix* result = string_to_matrix(formatted);
    free((void*)formatted);
    if (result == NULL) {
        errno = EINVAL;
        perror("fill_matrix_w_predicted_value (parse)");
        return NULL;
    }
    return result;
}

Matrix* fill_matrix() {
    int row, col, type_choice;
    printf("\n========================================\n");
    printf("         ВВОД НОВОЙ МАТРИЦЫ             \n");
    printf("========================================\n");
    if (!read_int("Количество строк: ", &row) || row <= 0) {
        errno = EINVAL;
        perror("fill_matrix (rows)");
        return NULL;
    }
    if (!read_int("Количество столбцов: ", &col) || col <= 0) {
        errno = EINVAL;
        perror("fill_matrix (cols)");
        return NULL;
    }
    printf("\n----------------------------------------\n");
    printf("Тип элементов матрицы:\n");
    printf("  1 — целые числа (int)\n");
    printf("  2 — вещественные числа (float)\n");
    printf("----------------------------------------\n");
    if (!read_int("Ваш выбор: ", &type_choice)) {
        errno = EINVAL;
        perror("fill_matrix (type input)");
        return NULL;
    }
    if (type_choice != 1 && type_choice != 2) {
        errno = EINVAL;
        perror("fill_matrix (type choice)");
        return NULL;
    }
    printf("========================================\n");
    char* data = get_string_from_user();
    if (data == NULL) {
        errno = EINVAL;
        perror("fill_matrix (data)");
        return NULL;
    }
     TypeElement* type = (type_choice == 1) ? &IntType : &FloatType;
     char* formatted = format_matrix(row, col, type, data);
    if (formatted == NULL) {
        errno = EINVAL;
        perror("fill_matrix (format)");
        return NULL;
    }
    Matrix* result = string_to_matrix(formatted);
    free((void*)formatted);
    if (result == NULL) {
        errno = EINVAL;
        perror("fill_matrix (parse)");
        return NULL;
    }
    return result;
}

void print_matrix_equality(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3, char* sign) {
    if (!matrix1 || !matrix2 || !matrix3) {
        return;
    }
     Element *elem;
    int fl = min(min(get_rows(matrix1), get_rows(matrix2)), get_rows(matrix3)) / 2;
    for (int i = 0; i < max(max(get_rows(matrix1), get_rows(matrix2)), get_rows(matrix3)); i++) {
        if (i < get_rows(matrix1)) {
            printf("│ ");
            for (int j = 0; j < get_cols(matrix1); j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index1 = i * get_cols(matrix1) + j;
                elem = get_element_by_index(get_array(matrix1), index1);
                if (elem) {
                    char* str = print(elem);
                    if (str) {
                        printf("%s", str);
                        free(str);
                    }
                }
            }
            printf("│");
        } else {
            for (int j = 0; j < get_cols(matrix1); j++) {
                for (int k = 0; k < WIDTH; k++) {
                    printf(" ");
                }
            }
        }
        printf("\t");
        if (i == fl) {
            printf("%s", sign);
        }
        if (i < get_rows(matrix2)) {
            printf("\t│ ");
            for (int j = 0; j < get_cols(matrix2); j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index2 = i * get_cols(matrix2) + j;
                elem = get_element_by_index(get_array(matrix2), index2);
                if (elem) {
                    char* str = print(elem);
                    if (str) {
                        printf("%s", str);
                        free(str);
                    }
                }
            }
            printf("│");
        } else {
            for (int j = 0; j < get_cols(matrix2); j++) {
                for (int k = 0; k < WIDTH; k++) {
                    printf(" ");
                }
            }
            printf("\t");
        }
        printf("\t");
        if (i == fl) {
            printf("=");
        }
        printf("\t");
        if (i < get_rows(matrix3)) {
            printf("│ ");
            for (int j = 0; j < get_cols(matrix3); j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index3 = i * get_cols(matrix3) + j;
                elem = get_element_by_index(get_array(matrix3), index3);
                if (elem) {
                    char* str = print(elem);
                    if (str) {
                        printf("%s", str);
                        free(str);
                    }
                }
            }
            printf("│");
        } else {
            for (int j = 0; j < get_cols(matrix3); j++) {
                for (int k = 0; k < WIDTH; k++) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void print_matrix_transition(Matrix* matrix1, Matrix* matrix2) {
    if (!matrix1 || !matrix2) {
        return;
    }
     Element *elem;
    int fl = max(get_rows(matrix1), get_rows(matrix2)) / 2;
    for (int i = 0; i < max(get_rows(matrix1), get_rows(matrix2)); i++) {
        if (i < get_rows(matrix1)) {
            printf("│ ");
            for (int j = 0; j < get_cols(matrix1); j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index1 = i * get_cols(matrix1) + j;
                elem = get_element_by_index(get_array(matrix1), index1);
                if (elem) {
                    char* str = print(elem);
                    if (str) {
                        printf("%s", str);
                        free(str);
                    }
                }
            }
            printf("│");
        } else {
            for (int j = 0; j < get_cols(matrix1); j++) {
                for (int k = 0; k < WIDTH; k++) {
                    printf(" ");
                }
            }
        }
        printf("\t");
        if (i == fl) {
            printf("%s", "->");
        }
        printf("\t ");
        if (i < get_rows(matrix2)) {
            printf("│ ");
            for (int j = 0; j < get_cols(matrix2); j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index2 = i * get_cols(matrix2) + j;
                elem = get_element_by_index(get_array(matrix2), index2);
                if (elem) {
                    char* str = print(elem);
                    if (str) {
                        printf("%s", str);
                        free(str);
                    }
                }
            }
            printf("│");
        }
        printf("\n");
    }
}

int start() {
    int choice;
    do {
        printf("\n========================================\n");
        printf("       МЕНЮ ОПЕРАЦИЙ С МАТРИЦАМИ        \n");
        printf("========================================\n");
        printf("1. Сложение матриц (A + B)\n");
        printf("2. Умножение матриц (A x B)\n");
        printf("3. Транспонирование матрицы (A^T)\n");
        printf("4. Линейная комбинация строк\n");
        printf("0. Выход\n");
        printf("----------------------------------------\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            errno = EINVAL;
            perror("start (input)");
            clear_buffer();
            continue;
        }
        clear_buffer();
        switch (choice) {
        case 1: {
            printf("\n--- СЛОЖЕНИЕ МАТРИЦ ---\n");
            Matrix* m1 = fill_matrix();
            if (m1 == NULL) {
                printf("Возврат в меню.\n");
                break;
            }
            Matrix* m2 = fill_matrix_w_predicted_value(
                get_array_type(get_array(m1)),
                get_rows(m1),
                get_cols(m1)
            );
            if (m2 == NULL) {
                printf("Возврат в меню.\n");
                destroy_matrix(m1);
                break;
            }
            Matrix* res = sum_matrix(m1, m2);
            if (res == NULL) {
                errno = EINVAL;
                perror("start (sum)");
            } else {
                print_matrix_equality(m1, m2, res, "+");
                destroy_matrix(res);
            }
            destroy_matrix(m1);
            destroy_matrix(m2);
            break;
        }
        case 2: {
            printf("\n--- УМНОЖЕНИЕ МАТРИЦ ---\n");
            Matrix* m1 = fill_matrix();
            if (m1 == NULL) {
                break;
            }
            Matrix* m2 = fill_matrix();
            if (m2 == NULL) {
                destroy_matrix(m1);
                break;
            }
            Matrix* res = mult_matrix(m1, m2);
            if (res == NULL) {
                errno = EINVAL;
                perror("start (mult)");
            } else {
                print_matrix_equality(m1, m2, res, "x");
                destroy_matrix(res);
            }
            destroy_matrix(m1);
            destroy_matrix(m2);
            break;
        }
        case 3: {
            printf("\n--- ТРАНСПОНИРОВАНИЕ ---\n");
            Matrix* m1 = fill_matrix();
            if (m1 == NULL) {
                break;
            }
            Matrix* res = transponate_matrix(m1);
            if (res == NULL) {
                errno = EINVAL;
                perror("start (transpose)");
            } else {
                print_matrix_transition(m1, res);
                destroy_matrix(res);
            }
            destroy_matrix(m1);
            break;
        }
        case 4: {
            printf("\n--- ЛИНЕЙНАЯ КОМБИНАЦИЯ СТРОК ---\n");
            Matrix* m1 = fill_matrix();
            if (m1 == NULL) {
                break;
            }
            int from_row, to_row;
            if (!read_int("Введите номер строки, ИЗ которой берем (от 1 до ...): ", &from_row) ||
                from_row < 1 || from_row > get_rows(m1)) {
                errno = EINVAL;
                perror("start (row num)");
                destroy_matrix(m1);
                break;
            }
            if (!read_int("Введите номер строки, К которой прибавляем (от 1 до ...): ", &to_row) ||
                to_row < 1 || to_row > get_rows(m1)) {
                errno = EINVAL;
                perror("start (row num)");
                destroy_matrix(m1);
                break;
            }
            Element* coeff = NULL;
             TypeElement* type = get_array_type(get_array(m1));
            if (type == &IntType) {
                int coeff_val;
                if (!read_int("Введите коэффициент (целое число): ", &coeff_val)) {
                    errno = EINVAL;
                    perror("start (coeff input)");
                    destroy_matrix(m1);
                    break;
                }
                coeff = create_int_elem();
                if (coeff) {
                    set_int_number(coeff, coeff_val);
                }
            } else if (type == &FloatType) {
                float coeff_val;
                printf("Введите коэффициент (вещественное число): ");
                if (scanf("%f", &coeff_val) != 1) {
                    errno = EINVAL;
                    perror("start (coeff input)");
                    clear_buffer();
                    destroy_matrix(m1);
                    break;
                }
                clear_buffer();
                coeff = create_float_elem();
                if (coeff) {
                    set_float_number(coeff, coeff_val);
                }
            }
            if (coeff == NULL) {
                errno = EINVAL;
                perror("start (coeff create)");
                destroy_matrix(m1);
                break;
            }
            Matrix* res = matrix_linear_combination(m1, from_row, to_row, coeff);
            if (res == NULL) {
                errno = EINVAL;
                perror("start (linear comb)");
            } else {
                print_matrix_transition(m1, res);
                destroy_matrix(res);
            }
            destroy_elem(coeff);
            destroy_matrix(m1);
            break;
        }
        case 0:
            printf("Выход из программы...\n");
            break;
        default:
            errno = EINVAL;
            perror("start (menu choice)");
            break;
        }
    } while (choice != 0);
    return 0;
}
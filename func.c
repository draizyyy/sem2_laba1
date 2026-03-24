#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "array.h"
#include "matrix.h"

#define WIDTH 6


// int scan_int(const Element* element) {
//     scanf("%d", (int*)element->number);
//     return 0;
// }

// int scan_float(const Element* element) {
//     scanf("%g", (float*)element->number);
//     return 0;
// }



int max(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    }
    return num2;
}

int min(int num1, int num2) {
    if (num1 < num2) {
        return num1;
    }
    return num2;
}

// void print_matrix(const Matrix* matrix) {
//     const Element *elem;
//     printf("\n");
//     for (int i = 0; i < matrix->row; i++) {
//         printf("│");
//         for (int j = 0; j < matrix->col; j++) {
//             if (j != 0) { printf(" "); }
//             int index = i * matrix->col + j;
//             elem = &matrix->massive[index];
//             print(elem);
//         }
//         printf("│\n");
//     }
// }



void print_matrix_equality(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3, char* sign) {
    const Element *elem;
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
                printf("%s", print(elem));
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
                // elem = &matrix2->massive[index2];
                printf("%s", print(elem));
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
                printf("%s", print(elem));            
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
    const Element *elem;
    printf("\n");
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
                printf("%s", print(elem));
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
                printf("%s", print(elem));
            } 
            printf("│");
        } else {
            printf(" ");
        }   
        printf("\n");
    }
}

// char* get_string_from_user() {
//     static char buffer[1024]; // static, чтобы вернуть указатель на данные
    
//     // Очищаем буфер ввода от лишнего мусора (например, оставшегося \n)
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF);

//     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//         // Убираем конечный \n, если он есть
//         size_t len = strlen(buffer);
//         if (len > 0 && buffer[len-1] == '\n') {
//             buffer[len-1] = '\0';
//         }
//         return buffer;
//     }
//     return NULL;
// }

char* get_string_from_user() {
    static char buffer[1024];
    char line[256];
    
    buffer[0] = '\0';  
    size_t total_len = 0;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Вводите числа (пустая строка для завершения):\n");
    
    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len-1] == '\n') {
            line[line_len-1] = '\0';
            line_len--;
        }
        
        if (line_len == 0) {
            if (total_len > 0) break;  
            else continue; 
        }
        
        if (total_len > 0 && total_len < sizeof(buffer) - 1) {
            buffer[total_len++] = ' ';
            buffer[total_len] = '\0';
        }
        
        if (total_len + line_len < sizeof(buffer) - 1) {
            strcpy(buffer + total_len, line);
            total_len += line_len;
        } else {
            fprintf(stderr, "Превышен лимит буфера (1024 символа)\n");
            break;
        }
    }
    
    return (total_len > 0) ? buffer : NULL;
}

const char* format_matrix(int rows, int cols, int type, const char* matrix_data) {
    size_t header_size = 50; 
    size_t data_size = strlen(matrix_data);
    size_t total_size = header_size + data_size + 1;
    
    
    char* result = (char*)malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    sprintf(result, "%d %d %d\n%s", rows, cols, type, matrix_data);

    return (const char*)result;
}

Matrix* fill_matrix_w_predicted_value(ElementType type) {
    int row, col;
    
    printf("\n========================================\n");
    printf("         ВВОД НОВОЙ МАТРИЦЫ             \n");
    printf("========================================\n");

    printf("Количество строк: ");
    if (scanf("%d", &row) != 1 || row <= 0) {
        printf("Ошибка: некорректное количество строк.\n");
        return NULL;
    }
    
    printf("Количество столбцов: ");
    if (scanf("%d", &col) != 1 || col <= 0) {
        printf("Ошибка: некорректное количество столбцов.\n");
        return NULL;
    }
    
    // printf("----------------------------------------\n");
    // printf("Введите элементы матрицы (по порядку):\n");
    // printf("----------------------------------------\n");   

    int value;
    if (type == TYPE_INT) {
        value = 1;
    } else if (type == TYPE_FLOAT) {
        value = 2;
    } else {
        return NULL;
    }

    printf("========================================\n");
    return string_to_matrix(format_matrix(row, col, value, get_string_from_user()));
}

Matrix* fill_matrix() {
    int row, col;
    
    printf("\n========================================\n");
    printf("         ВВОД НОВОЙ МАТРИЦЫ             \n");
    printf("========================================\n");

    printf("Количество строк: ");
    if (scanf("%d", &row) != 1 || row <= 0) {
        printf("Ошибка: некорректное количество строк.\n");
        return NULL;
    }
    
    printf("Количество столбцов: ");
    if (scanf("%d", &col) != 1 || col <= 0) {
        printf("Ошибка: некорректное количество столбцов.\n");
        return NULL;
    }
    
    printf("\n");
    printf("----------------------------------------\n");
    printf("Тип элементов матрицы:\n");
    printf("  1 — целые числа (int)\n");
    printf("  2 — вещественные числа (float)\n");
    printf("----------------------------------------\n");
    printf("Ваш выбор: ");
    
    int value;
    scanf("%d", &value);
    
    // printf("----------------------------------------\n");
    // printf("Введите элементы матрицы (по порядку):\n");
    // printf("----------------------------------------\n");   

    printf("========================================\n");
    return string_to_matrix(format_matrix(row, col, value, get_string_from_user()));
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
        printf("4. Прибавление линейной комбинации строк\n");
        printf("0. Выход\n");
        printf("----------------------------------------\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Попробуйте снова.\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1: {
                printf("\n--- СЛОЖЕНИЕ МАТРИЦ ---\n");
                // printf("Введите первую матрицу:\n");
                Matrix* m1 = fill_matrix();
                // printf("Введите вторую матрицу:\n");
                Matrix* m2 = fill_matrix_w_predicted_value(get_array_type(get_array(m1)));

                Matrix* res = sum_matrix(m1, m2);

                if (res == NULL) {
                    printf("Ошибка сложения");
                    break;
                }
                
                print_matrix_equality(m1, m2, res, "+");
                
                // free_matrix(m1); free_matrix(m2); free_matrix(res);
                break;
            }
            case 2: {
                printf("\n--- УМНОЖЕНИЕ МАТРИЦ ---\n");
                // printf("Введите первую матрицу:\n");
                Matrix* m1 = fill_matrix();
                // printf("Введите вторую матрицу:\n");
                Matrix* m2 = fill_matrix_w_predicted_value(get_array_type(get_array(m1)));
                
                Matrix* res = mult_matrix(m1, m2);
                print_matrix_equality(m1, m2, res, "x");
                
                // free_matrix(m1); free_matrix(m2); free_matrix(res);
                break;
            }
            case 3: {
                printf("\n--- ТРАНСПОНИРОВАНИЕ ---\n");
                // printf("Введите матрицу:\n");
                Matrix* m1 = fill_matrix();
                
                Matrix* res = transponate_matrix(m1);
                print_matrix_transition(m1, res);
                
                // free_matrix(m1); free_matrix(res);
                break;
            }
            case 4: {
                printf("\n--- ЛИНЕЙНАЯ КОМБИНАЦИЯ СТРОК ---\n");
                // printf("Введите матрицу:\n");
                Matrix* m1 = fill_matrix();
                
                int from_row, to_row;
                
                
                printf("Введите номер строки, ИЗ которой берем (от 1 до %d): ", get_rows(m1));
                scanf("%d", &from_row);
                
                printf("Введите номер строки, К которой прибавляем (от 1 до %d): ", get_rows(m1));
                scanf("%d", &to_row);


                Element* elem;
                printf("Введите коэффициент (число): ");
                if (get_array_type(get_array(m1)) == TYPE_INT) {
                    int coeff_val;
                    scanf("%d", &coeff_val);
                    elem = create_int_elem();
                    set_int_number(elem, coeff_val);
                }
                else if (get_array_type(get_array(m1)) == TYPE_FLOAT) {
                    float coeff_val;
                    scanf("%f", &coeff_val);
                    elem = create_float_elem();
                    set_float_number(elem, coeff_val);
                }
                else {
                    break;
                }
                
                
                Matrix* res = matrix_linear_combination(m1, from_row, to_row, elem);
                print_matrix_transition(m1, res);
                
                // free_matrix(m1); free_matrix(res);
                break;
            }
            case 0:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный номер пункта меню. Попробуйте снова.\n");
        }
        
    } while (choice != 0);

    return 0;
}


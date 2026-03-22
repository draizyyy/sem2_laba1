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
    printf("\n");
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
                print(elem);                
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
                print(elem); 
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
                print(elem);
            } 
            printf("│");
        } else {
            printf(" ");
        }   
        printf("\n");
    }
}

const char* get_string_from_user() {
    static char str[100];

    scanf("%99s", str);
    
    return str;
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
    // Array* array = create_array_size_element(row * col);
    // switch (value) {
    //     case 1:
    //         for (int i = 0; i < row * col; i++) {
    //             set_element_by_index(array, i, create("int"));
    //         }
    //         break;
    //     case 2:
    //         for (int i = 0; i < row * col; i++) {
    //             set_element_by_index(array, i, create("float"));
    //         }
    //         break;
    //     default:
    //         printf("Ошибка: неверный тип данных.\n");
    //         return NULL;
    // }
    
    
    printf("----------------------------------------\n");
    printf("Введите элементы матрицы (по порядку):\n");
    printf("----------------------------------------\n");   

    // for (int i = 0; i < get_rows(matrix); i++) {
    //     for (int j = 0; j < get_cols(matrix); j++) {
    //         int index = i * get_cols(matrix) + j;
            
    //         set_element_by_index(get_array(matrix), index, );
    //         matrix->massive[index].type_info->scan(&matrix->massive[index]);
    //     }
    // }
    
    printf("========================================\n");
    return string_to_matrix(format_matrix(row, col, value, get_string_from_user()));
}

// int test1() {
//     printf("test1");
//     const char* input1 = "2 2 1\n1 2\n3 4\n";
//     const char* input2 = "2 2 1\n3 4\n1 2\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix2 = fill_matrix_from_string(input2);
//     Matrix* matrix3 = sum_matrix(matrix1, matrix2);
//     Matrix* matrix4 = mult_matrix(matrix1, matrix2);
//     print_matrix_equality(matrix1, matrix2, matrix3, "+");
//     print_matrix_equality(matrix1, matrix2, matrix4, "x");
//     return 0;
// }

// int test2() {
//     printf("test2");
//     const char* input1 = "2 3 1\n1 2 3\n4 5 6\n";
//     const char* input2 = "3 2 1\n4 5\n6 7\n8 9\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix2 = fill_matrix_from_string(input2);
//     Matrix* matrix4 = mult_matrix(matrix1, matrix2);
//     print_matrix_equality(matrix1, matrix2, matrix4, "x");
//     return 0;
// }

// int test3() {
//     printf("test3");
//     const char* input1 = "3 2 1\n1 2\n3 4\n5 6\n";
//     const char* input2 = "2 4 1\n3 4 5 6\n7 8 9 10\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix2 = fill_matrix_from_string(input2);
//     Matrix* matrix4 = mult_matrix(matrix1, matrix2);
//     print_matrix_equality(matrix1, matrix2, matrix4, "x");
//     return 0;
// }

// int test4() {
//     printf("test4");
//     const char* input1 = "1 4 1\n1 2 3 4\n";
//     const char* input2 = "4 1 1\n5\n6\n7\n8\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix2 = fill_matrix_from_string(input2);
//     Matrix* matrix4 = mult_matrix(matrix1, matrix2);
//     print_matrix_equality(matrix1, matrix2, matrix4, "x");
//     return 0;
// }

// int test5() {
//     printf("test5");
//     const char* input1 = "4 1 1\n1\n2\n3\n4\n";
//     const char* input2 = "1 4 1\n2 3 4 5\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix2 = fill_matrix_from_string(input2);
//     Matrix* matrix4 = mult_matrix(matrix1, matrix2);
//     print_matrix_equality(matrix1, matrix2, matrix4, "x");
//     return 0;
// }

// int test6() {
//     printf("test6");
//     const char* input1 = "2 3 1\n1 2 3\n4 5 6\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix5 = transponate_matrix(matrix1);
//     print_matrix_transition(matrix1, matrix5);
//     return 0;
// }

// int test7() {
//     printf("test7");
//     const char* input1 = "3 2 1\n1 2\n3 4\n5 6\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix5 = transponate_matrix(matrix1);
//     print_matrix_transition(matrix1, matrix5);
//     return 0;
// }

// int test8() {
//     printf("test8");
//     const char* input1 = "1 4 1\n1 2 3 4\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix5 = transponate_matrix(matrix1);
//     print_matrix_transition(matrix1, matrix5);
//     return 0;
// }

// int test9() {
//     printf("test9");
//     const char* input1 = "4 1 1\n1\n2\n3\n4\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix5 = transponate_matrix(matrix1);
//     print_matrix_transition(matrix1, matrix5);
//     return 0;
// }

// int test10() {
//     printf("test10");
//     const char* input1 = "3 3 1\n1 2 3\n4 5 6\n7 8 9\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Matrix* matrix5 = transponate_matrix(matrix1);
//     print_matrix_transition(matrix1, matrix5);
//     return 0;
// }

// int test11() {
//     printf("test11");
//     const char* input1 = "2 2 2\n1 2\n3 4\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Element elem = create_float_elem();
//     *(float*)elem.number = 1.0;
//     Matrix* matrix6 = matrix_linear_combination(matrix1, 1, 2, elem);
//     print_matrix_transition(matrix1, matrix6);
//     return 0;
// }

// int test12() {
//     printf("test12");
//     const char* input1 = "2 2 1\n1 0\n0 1\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Element elem = create_float_elem();
//     *(int*)elem.number = 0;
//     Matrix* matrix6 = matrix_linear_combination(matrix1, 2, 1, elem);
//     print_matrix_transition(matrix1, matrix6);
//     return 0;
// }

// int test13() {
//     printf("test13");
//     const char* input1 = "2 2 1\n1 2\n3 4\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Element elem = create_float_elem();
//     *(int*)elem.number = 5.0;
//     Matrix* matrix6 = matrix_linear_combination(matrix1, 1, 2, elem);
//     print_matrix_transition(matrix1, matrix6);
//     return 0;
// }

// int test14() {
//     printf("test14");
//     const char* input1 = "3 3 2\n1 1 1\n1 1 1\n1 1 1\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Element elem = create_float_elem();
//     *(float*)elem.number = 2.0;
//     Matrix* matrix6 = matrix_linear_combination(matrix1, 3, 2, elem);
//     print_matrix_transition(matrix1, matrix6);
//     return 0;
// }

// int test15() {
//     printf("test15");
//     const char* input1 = "2 3 2\n1 2 3\n4 5 6\n";
//     Matrix* matrix1 = fill_matrix_from_string(input1);
//     Element elem = create_float_elem();
//     *(float*)elem.number = 1.0;
//     Matrix* matrix6 = matrix_linear_combination(matrix1, 2, 1, elem);
//     print_matrix_transition(matrix1, matrix6);
//     return 0;
// }

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
                Matrix* m2 = fill_matrix();
                
                Matrix* res = sum_matrix(m1, m2);
                print_matrix_equality(m1, m2, res, "+");
                
                // free_matrix(m1); free_matrix(m2); free_matrix(res);
                break;
            }
            case 2: {
                printf("\n--- УМНОЖЕНИЕ МАТРИЦ ---\n");
                // printf("Введите первую матрицу:\n");
                Matrix* m1 = fill_matrix();
                // printf("Введите вторую матрицу:\n");
                Matrix* m2 = fill_matrix();
                
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
                float coeff_val;
                
                printf("Введите номер строки, ИЗ которой берем (from_row, начиная с 0): ");
                scanf("%d", &from_row);
                
                printf("Введите номер строки, К которой прибавляем (to_row, начиная с 0): ");
                scanf("%d", &to_row);
                
                printf("Введите коэффициент (число): ");
                scanf("%f", &coeff_val);
                
                Element* elem = create_float_elem();
                set_float_number(elem, coeff_val);
                
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


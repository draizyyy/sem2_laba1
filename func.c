#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "massive.h"

#define WIDTH 6

const TypeInfo IntType = {
    .scan = scan_int,
    .print = print_int,
    .destroy = destroy_elem,
    .compare = compare_int,
    .multiply = mult_int,
    .sum = sum_int,
    .create = create_int_elem,
    .create_null_elem = create_null_elem_int
};

const TypeInfo FloatType = {
    .scan = scan_float,
    .print = print_float,
    .destroy = destroy_elem,
    .compare = compare_float,
    .multiply = mult_float,
    .sum = sum_float,
    .create = create_float_elem,
    .create_null_elem = create_null_elem_float
};

void scan_int(const Element* element) {
    scanf("%d", (int*)element->number);
}

void scan_float(const Element* element) {
    scanf("%g", (float*)element->number);
}

void print_int(const Element* element) {
    printf("%-5d", *(int*)element->number);
}

void print_float(const Element* element) {
    printf("%-5g", *(float*)element->number);
}

int compare_int(const Element* element1, const Element* element2) {
    int num1 = *(const int*)(*element1).number;
    int num2 = *(const int*)(*element2).number;

    if (num1 == num2) {
        return 1;
    }
    return 0;
}

int compare_float(const Element* element1, const Element* element2) {
    float num1 = *(const float*)(*element1).number;
    float num2 = *(const float*)(*element2).number;

    if (num1 == num2) {
        return 1;
    }
    return 0;
}

void destroy_elem (Element* elem) {
    free(elem->number);
    elem->number = NULL;
}

Element create_int_elem() {
    Element elem;
    elem.size = sizeof(int);
    elem.type_info = &IntType;

    elem.number = malloc(elem.size);
    
    if (elem.number == NULL) {
        return elem;
    }

    return elem;
}

Element create_float_elem() {
    Element elem;
    elem.size = sizeof(float);
    elem.type_info = &FloatType;

    elem.number = malloc(elem.size);
    if (elem.number == NULL) {
        return elem;
    }

    return elem;
}

Element create_null_elem_int() {
    Element elem;
    elem.size = sizeof(int);
    elem.type_info = &IntType;

    elem.number = malloc(elem.size);
    if (elem.number == NULL) {
        return elem;
    }

    *(int*)elem.number = 0;

    return elem;
}

Element create_null_elem_float() {
    Element elem;
    elem.size = sizeof(float);
    elem.type_info = &FloatType;

    elem.number = malloc(elem.size);
    if (elem.number == NULL) {
        return elem;
    }

    *(float*)elem.number = 0.0f;

    return elem;
}

Element sum_int(const Element* element1, const Element* element2) {
    int num1 = *(const int*)(*element1).number;
    int num2 = *(const int*)(*element2).number;

    Element new_elem = create_int_elem();

    *(int*)new_elem.number = num1 + num2;

    return new_elem;
}

Element sum_float(const Element* element1, const Element* element2) {
    float num1 = *(const float*)(*element1).number;
    float num2 = *(const float*)(*element2).number;

    Element new_elem = create_float_elem();

    *(float*)new_elem.number = num1 + num2;

    return new_elem;
}

Element sum(const Element* left, const Element* right) {
    return left->type_info->sum(left, right);
}

Element mult_int(const Element* element1, const Element* element2) {
    int num1 = *(const int*)(*element1).number;
    int num2 = *(const int*)(*element2).number;

    Element new_elem = create_int_elem();

    *(int*)new_elem.number = num1 * num2;

    return new_elem;
}

Element mult_float(const Element* element1, const Element* element2) {
    float num1 = *(const float*)(*element1).number;
    float num2 = *(const float*)(*element2).number;

    Element new_elem = create_float_elem();

    *(float*)new_elem.number = num1 * num2;

    return new_elem;
}

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

void print_matrix(const Matrix* matrix) {
    const Element *elem;
    printf("\n");
    for (int i = 0; i < matrix->row; i++) {
        printf("│");
        for (int j = 0; j < matrix->col; j++) {
            if (j != 0) { printf(" "); }
            int index = i * matrix->col + j;
            elem = &matrix->massive[index];
            elem->type_info->print(elem);
        }
        printf("│\n");
    }
}

void print_matrix_equality(const Matrix* matrix1, const Matrix* matrix2, const Matrix* matrix3, char* sign) {
    const Element *elem;
    printf("\n");
    int fl = min(min(matrix1->row, matrix2->row), matrix3->row) / 2;
    for (int i = 0; i < max(max(matrix1->row, matrix2->row), matrix3->row); i++) {
        

        if (i < matrix1->row) {
            printf("│ ");
            for (int j = 0; j < matrix1->col; j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index1 = i * matrix1->col + j;

                elem = &matrix1->massive[index1];
                elem->type_info->print(elem);
            } 
            printf("│");
        } else {
            for (int j = 0; j < matrix1->col; j++) {
                for (int k = 0; k < WIDTH; k++) {
                    printf(" ");
                }   
            }
        }   
        printf("\t");
        
        
        if (i == fl) {
            printf("%s", sign);
        }

        if (i < matrix2->row) {
            printf("\t│ ");
            for (int j = 0; j < matrix2->col; j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index2 = i * matrix2->col + j;

                elem = &matrix2->massive[index2];
                elem->type_info->print(elem);
            } 
            printf("│");
        } else {
            for (int j = 0; j < matrix2->col; j++) {
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
        if (i < matrix3->row) {
            printf("│ ");
            for (int j = 0; j < matrix3->col; j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index3 = i * matrix3->col + j;

                elem = &matrix3->massive[index3];
                elem->type_info->print(elem);
                
            } 
            printf("│");
        } else {
            for (int j = 0; j < matrix3->col; j++) {
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
    int fl = max(matrix1->row, matrix2->row) / 2;
    for (int i = 0; i < max(matrix1->row, matrix2->row); i++) {
        printf("│ ");

        if (i < matrix1->row) {
            for (int j = 0; j < matrix1->col; j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index1 = i * matrix1->col + j;

                elem = &matrix1->massive[index1];
                elem->type_info->print(elem);
            } 
        } else {
            printf("\t\t");
        }   
        
        printf("│\t");
        
        if (i == fl) {
            printf("%s", "->");
        }

        printf("\t│ ");

        if (i < matrix2->row) {
            for (int j = 0; j < matrix2->col; j++) {
                if (j != 0) {
                    printf(" ");
                }
                int index2 = i * matrix2->col + j;

                elem = &matrix2->massive[index2];
                elem->type_info->print(elem);
            } 
        } else {
            printf("\t\t");
        }   
        printf("│\n");
    }
}

Matrix* create_matrix(Element* massive, int row, int col) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->col = col;
    matrix->row = row;
    matrix->massive = massive;

    return matrix;
}

// Matrix* fill_matrix() {
//     int row, col;
//     printf("Введите количество строк: ");
//     if (scanf("%d", &row) != 1 || row <= 0) {
//         printf("Ошибка: некорректное количество строк.\n");
//         return NULL;
//     }

//     printf("Введите количество столбцов: ");
//     if (scanf("%d", &col) != 1 || col <= 0) {
//         printf("Ошибка: некорректное количество столбцов.\n");
//         return NULL;
//     }

//     Element* massive = create_massive_size(row * col);
    
//     printf("Введите 1 если матрица целочисленная, 2 если с дробными числами: ");
//     int value;
//     scanf("%d", &value);
//     switch (value) {
//         case 1:
//             for (int i = 0; i < row * col; i++) {
//                 massive[i] = create_int_elem();
//             }
//             break;
//         case 2:
//             for (int i = 0; i < row * col; i++) {
//                 massive[i] = create_float_elem();
//             }
//             break;
//         default:
//             printf("Неверный ввод, попробуйте ещё раз");
//             return NULL;
//     }


//     Matrix* matrix = create_matrix(massive, row, col);

//     printf("Введите матрицу:\n");

//     // printf("%d ", matrix->row);
//     // printf("%d", matrix->col);
//     // printf("\n");
//     for (int i = 0; i < matrix->row; i++) {
//         for (int j = 0; j < matrix->col; j++) {
//             // printf("%d ", i);
//             // printf("%d", j);
//             // printf("\n");
//             int index = i * matrix->col + j;
//             matrix->massive[index].type_info->scan(&matrix->massive[index]);
//         }
//     }

//     return matrix;
// }

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
    Element* massive = create_massive_size(row * col);
    
    switch (value) {
        case 1:
            for (int i = 0; i < row * col; i++) {
                massive[i] = create_int_elem();
            }
            break;
        case 2:
            for (int i = 0; i < row * col; i++) {
                massive[i] = create_float_elem();
            }
            break;
        default:
            printf("Ошибка: неверный тип данных.\n");
            return NULL;
    }
    
    Matrix* matrix = create_matrix(massive, row, col);
    
    
    printf("----------------------------------------\n");
    printf("Введите элементы матрицы (по порядку):\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            int index = i * matrix->col + j;
            matrix->massive[index].type_info->scan(&matrix->massive[index]);
        }
    }
    
    printf("========================================\n");
    return matrix;
}

// Matrix* fill_matrix_from_string(const char* input) {
//     int row, col, type;
//     int offset = 0, consumed = 0;
    
//     if (sscanf(input + offset, "%d %d %d%n", &row, &col, &type, &consumed) != 3) {
//         printf("Ошибка: неверный формат.\n");
//         return NULL;
//     }
//     offset += consumed;
    
//     if (row <= 0 || col <= 0 || (type != 1 && type != 2)) {
//         printf("Ошибка: некорректные параметры.\n");
//         return NULL;
//     }
    
//     Element* massive = create_massive_size(row * col);
//     for (int i = 0; i < row * col; i++) {
//         massive[i] = (type == 1) ? create_int_elem() : create_float_elem();
//     }
    
//     Matrix* matrix = create_matrix(massive, row, col);

//     for (int i = 0; i < row * col; i++) {
//         if (type == 1) {
//             int val;
//             if (sscanf(input + offset, "%d%n", &val, &consumed) != 1) {
//                 printf("Ошибка: не хватает чисел.\n");
//                 // destroy_matrix(matrix);
//                 return NULL;
//             }
//             *(int*)matrix->massive[i].number = val;
//         } else {
//             float val;
//             if (sscanf(input + offset, "%f%n", &val, &consumed) != 1) {
//                 printf("Ошибка: не хватает чисел.\n");
//                 // destroy_matrix(matrix);
//                 return NULL;
//             }
//             *(float*)matrix->massive[i].number = val;
//         }
//         offset += consumed;
//     }
    
//     return matrix;
// }

Matrix* fill_matrix_from_string(const char* input) {
    int row, col, type;
    int offset = 0, consumed = 0;
    
    if (sscanf(input + offset, "%d %d %d%n", &row, &col, &type, &consumed) != 3) {
        printf("Ошибка: неверный формат.\n");
        return NULL;
    }
    offset += consumed;
    
    if (row <= 0 || col <= 0 || (type != 1 && type != 2)) {
        printf("Ошибка: некорректные параметры.\n");
        return NULL;
    }
    
    Element* massive = create_massive_size(row * col);
    for (int i = 0; i < row * col; i++) {
        massive[i] = (type == 1) ? create_int_elem() : create_float_elem();
    }
    
    Matrix* matrix = create_matrix(massive, row, col);

    for (int i = 0; i < row * col; i++) {
        if (type == 1) {
            int val;
            if (sscanf(input + offset, "%d%n", &val, &consumed) != 1) {
                printf("Ошибка: не хватает чисел.\n");
                return NULL;
            }
            *(int*)matrix->massive[i].number = val;
        } else {
            float val;
            if (sscanf(input + offset, "%f%n", &val, &consumed) != 1) {
                printf("Ошибка: не хватает чисел.\n");
                return NULL;
            }
            *(float*)matrix->massive[i].number = val;
        }
        offset += consumed;
    }
    
    return matrix;
}

Matrix* sum_matrix(Matrix* matrix1, Matrix* matrix2) {
    if ((matrix1->col != matrix2->col) || (matrix1->row != matrix2->row)) {
        return NULL;
    }

    Element* massive = create_massive_size(matrix1->row * matrix1->col);

    for (int i = 0; i < matrix1->row * matrix1->col; i++) {
        massive[i] = *(const Element*)matrix1->massive[0].type_info->create;
    }
    
    Matrix* matrix = create_matrix(massive, matrix1->row, matrix1->col);

    for (int i = 0; i < matrix1->row; i++) {
        for (int j = 0; j < matrix1->col; j++) {
            int index = i * matrix->col + j;
            matrix->massive[index] = matrix1->massive[0].type_info->sum(&matrix1->massive[index], &matrix2->massive[index]);
        }
    }

    return matrix;
}

// Matrix* mult_matrix(Matrix* matrix1, Matrix* matrix2) {
//     if (matrix1->col != matrix2->row) {
//         return NULL;
//     }

//     Element* massive = create_massive_size(matrix1->row * matrix2->col);

//     for (int i = 0; i < matrix1->row * matrix2->col; i++) {
//         massive[i] = matrix1->massive[0].type_info->create_null_elem();
//     }
    
//     Matrix* matrix = create_matrix(massive, matrix1->row, matrix2->col);

//     for (int i = 0; i < matrix1->row; i++) {
//         for (int j = 0; j < matrix2->col; j++) {
//             int index = i * matrix2->col + j;
//             for (int k = 0; k < matrix1->col; k++) {
//                 int index_left = k * matrix2->col + j;
//                 int index_right = i * matrix1->col + k;

//                 Element elem = matrix1->massive[0].type_info->multiply(&matrix1->massive[index_left], &matrix2->massive[index_right]);
//                 Element old_elem = matrix->massive[index];
//                 matrix->massive[index] = matrix1->massive[0].type_info->sum(&elem, &old_elem);
//             } 
//         }
//     }

//     return matrix;
// }

Matrix* mult_matrix(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1->col != matrix2->row) {
        return NULL;
    }

    Element* massive = create_massive_size(matrix1->row * matrix2->col);

    for (int i = 0; i < matrix1->row * matrix2->col; i++) {
        massive[i] = matrix1->massive[0].type_info->create_null_elem();
    }
    
    Matrix* matrix = create_matrix(massive, matrix1->row, matrix2->col);

    for (int i = 0; i < matrix1->row; i++) {
        for (int j = 0; j < matrix2->col; j++) {
            int index = i * matrix->col + j;
            for (int k = 0; k < matrix1->col; k++) {
                int index_left = i * matrix1->col + k;
                int index_right = k * matrix2->col + j;

                Element elem = matrix1->massive[0].type_info->multiply(&matrix1->massive[index_left], &matrix2->massive[index_right]);
                Element old_elem = matrix->massive[index];
                matrix->massive[index] = matrix1->massive[0].type_info->sum(&elem, &old_elem);
            } 
        }
    }

    return matrix;
}

Matrix* transponate_matrix(Matrix* matrix) {
    Element* massive = create_massive_size(matrix->row * matrix->col);

    for (int i = 0; i < matrix->row * matrix->col; i++) {
        massive[i] = matrix->massive[0].type_info->create();
    }
    
    Matrix* new_matrix = create_matrix(massive, matrix->col, matrix->row);

    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            int index = i * matrix->col + j;
            int new_index = j * matrix->row + i;
            new_matrix->massive[new_index] = matrix->massive[index];
        }
    }

    return new_matrix;
}

// Предполагается, что структура Matrix определена где-то выше
// typedef struct { ... } Matrix;

// void add_row_multiplied(Matrix* matrix) {
//     int target_row_input, source_row_input;
//     double coefficient;

//     // --- 1. Ввод строки, которую изменяем ---
//     while (1) {
//         printf("Введите номер строки, которую нужно изменить (от 1 до %d): ", matrix->row);
        
//         // Проверка успешности ввода числа
//         if (scanf("%d", &target_row_input) != 1) {
//             printf("Ошибка: нужно ввести число!\n");
//             while (getchar() != '\n'); // Очистка буфера ввода
//             continue;
//         }
        
//         // Проверка диапазона
//         if (target_row_input >= 1 && target_row_input <= matrix->row) {
//             break; // Ввод корректен
//         }
        
//         printf("Ошибка: номер строки вне диапазона (1-%d)!\n", matrix->row);
//         while (getchar() != '\n'); // Очистка буфера
//     }

//     // --- 2. Ввод строки, которую прибавляем ---
//     while (1) {
//         printf("Введите номер строки, которую нужно прибавить (от 1 до %d): ", matrix->row);
        
//         if (scanf("%d", &source_row_input) != 1) {
//             printf("Ошибка: нужно ввести число!\n");
//             while (getchar() != '\n');
//             continue;
//         }
        
//         if (source_row_input >= 1 && source_row_input <= matrix->row) {
//             break;
//         }
        
//         printf("Ошибка: номер строки вне диапазона (1-%d)!\n", matrix->row);
//         while (getchar() != '\n');
//     }

//     // --- 3. Ввод коэффициента ---
//     printf("Введите коэффициент умножения: ");
//     scanf("%lf", &coefficient);
    
//     // Очистка буфера после ввода double (на случай если дальше будет ввод char/string)
//     while (getchar() != '\n'); 

//     // --- Подготовка индексов для работы с массивом (0-based) ---
//     // Пользователь ввел 1..N, нам нужно 0..N-1
//     int target_index = target_row_input - 1;
//     int source_index = source_row_input - 1;

//     printf("\nПараметры приняты:\n");
//     printf("Изменяем строку #%d (индекс %d)\n", target_row_input, target_index);
//     printf("Прибавляем строку #%d (индекс %d) * %lf\n", source_row_input, source_index, coefficient);

//     // ... Дальше идет логика самого сложения строк ...
// }

Matrix* matrix_linear_combination(Matrix* matrix, int from_row, int to_row, Element coeff) {
    Element* massive = create_massive_size(matrix->row * matrix->col);

    for (int i = 0; i < matrix->row * matrix->col; i++) {
        massive[i] = *(const Element*)matrix->massive[0].type_info->create;
    }
    
    Matrix* new_matrix = create_matrix(massive, matrix->row, matrix->col);

    // printf("Введите номер строки от 1 до %d, к которой хотите прибавить: ", matrix->row);
    // scanf("%d", &to_row);
    // printf("\nВведите номер строки от 1 до %d, которую хотите прибавить: ", matrix->row);
    // scanf("%d", &from_row);
    // printf("\nВведите коэффициент на который нужно умножить: ");
    // matrix->massive[0].type_info->scan(&elem);
    // printf("\n");

    to_row--, from_row--;

    
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            int index = i * matrix->col + j;
            new_matrix->massive[index] = matrix->massive[index];
        }
    }

    int index_to = to_row * new_matrix->row, index_from = from_row * new_matrix->row;
    for (int j = 0; j < new_matrix->col; j++, index_to++, index_from++) {
        Element from_elem = new_matrix->massive[0].type_info->multiply(&coeff, &new_matrix->massive[index_from]);
        Element to_elem = new_matrix->massive[index_to];
        new_matrix->massive[index_to] = new_matrix->massive[0].type_info->sum(&from_elem, &to_elem);
    }
    return new_matrix;
}


int test1() {
    printf("test1");
    const char* input1 = "2 2 1\n1 2\n3 4\n";
    const char* input2 = "2 2 1\n3 4\n1 2\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix2 = fill_matrix_from_string(input2);
    Matrix* matrix3 = sum_matrix(matrix1, matrix2);
    Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    print_matrix_equality(matrix1, matrix2, matrix3, "+");
    print_matrix_equality(matrix1, matrix2, matrix4, "x");
    return 0;
}

int test2() {
    printf("test2");
    const char* input1 = "2 3 1\n1 2 3\n4 5 6\n";
    const char* input2 = "3 2 1\n4 5\n6 7\n8 9\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix2 = fill_matrix_from_string(input2);
    Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    print_matrix_equality(matrix1, matrix2, matrix4, "x");
    return 0;
}

int test3() {
    printf("test3");
    const char* input1 = "3 2 1\n1 2\n3 4\n5 6\n";
    const char* input2 = "2 4 1\n3 4 5 6\n7 8 9 10\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix2 = fill_matrix_from_string(input2);
    Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    print_matrix_equality(matrix1, matrix2, matrix4, "x");
    return 0;
}

int test4() {
    printf("test4");
    const char* input1 = "1 4 1\n1 2 3 4\n";
    const char* input2 = "4 1 1\n5\n6\n7\n8\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix2 = fill_matrix_from_string(input2);
    Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    print_matrix_equality(matrix1, matrix2, matrix4, "x");
    return 0;
}

int test5() {
    printf("test5");
    const char* input1 = "4 1 1\n1\n2\n3\n4\n";
    const char* input2 = "1 4 1\n2 3 4 5\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix2 = fill_matrix_from_string(input2);
    Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    print_matrix_equality(matrix1, matrix2, matrix4, "x");
    return 0;
}

int test6() {
    printf("test6");
    const char* input1 = "2 3 1\n1 2 3\n4 5 6\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix5 = transponate_matrix(matrix1);
    print_matrix_transition(matrix1, matrix5);
    return 0;
}

int test7() {
    printf("test7");
    const char* input1 = "3 2 1\n1 2\n3 4\n5 6\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix5 = transponate_matrix(matrix1);
    print_matrix_transition(matrix1, matrix5);
    return 0;
}

int test8() {
    printf("test8");
    const char* input1 = "1 4 1\n1 2 3 4\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix5 = transponate_matrix(matrix1);
    print_matrix_transition(matrix1, matrix5);
    return 0;
}

int test9() {
    printf("test9");
    const char* input1 = "4 1 1\n1\n2\n3\n4\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix5 = transponate_matrix(matrix1);
    print_matrix_transition(matrix1, matrix5);
    return 0;
}

int test10() {
    printf("test10");
    const char* input1 = "3 3 1\n1 2 3\n4 5 6\n7 8 9\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Matrix* matrix5 = transponate_matrix(matrix1);
    print_matrix_transition(matrix1, matrix5);
    return 0;
}

int test11() {
    printf("test11");
    const char* input1 = "2 2 2\n1 2\n3 4\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Element elem = create_float_elem();
    *(float*)elem.number = 1.0;
    Matrix* matrix6 = matrix_linear_combination(matrix1, 1, 2, elem);
    print_matrix_transition(matrix1, matrix6);
    return 0;
}

int test12() {
    printf("test12");
    const char* input1 = "2 2 1\n1 0\n0 1\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Element elem = create_float_elem();
    *(int*)elem.number = 0;
    Matrix* matrix6 = matrix_linear_combination(matrix1, 2, 1, elem);
    print_matrix_transition(matrix1, matrix6);
    return 0;
}

int test13() {
    printf("test13");
    const char* input1 = "2 2 1\n1 2\n3 4\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Element elem = create_float_elem();
    *(int*)elem.number = 5.0;
    Matrix* matrix6 = matrix_linear_combination(matrix1, 1, 2, elem);
    print_matrix_transition(matrix1, matrix6);
    return 0;
}

int test14() {
    printf("test14");
    const char* input1 = "3 3 2\n1 1 1\n1 1 1\n1 1 1\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Element elem = create_float_elem();
    *(float*)elem.number = 2.0;
    Matrix* matrix6 = matrix_linear_combination(matrix1, 3, 2, elem);
    print_matrix_transition(matrix1, matrix6);
    return 0;
}

int test15() {
    printf("test15");
    const char* input1 = "2 3 2\n1 2 3\n4 5 6\n";
    Matrix* matrix1 = fill_matrix_from_string(input1);
    Element elem = create_float_elem();
    *(float*)elem.number = 1.0;
    Matrix* matrix6 = matrix_linear_combination(matrix1, 2, 1, elem);
    print_matrix_transition(matrix1, matrix6);
    return 0;
}

int start() {
    // // while (1) {
    // //     printf("Привет, ");
    // // }
    // const char* input1 = "3 3 2\n"
    // "1 2 3\n"
    // "4 5 6\n"
    // "7 8 9\n";
    // const char* input2 = "3 3 2\n"
    // "2 3 2\n"
    // "4 3 4\n"
    // "2 3 2\n";

    // Element elem = create_float_elem();
    // *(float*)elem.number = 5.0;

    // Matrix* matrix1 = fill_matrix();
    // Matrix* matrix2 = fill_matrix();
    // Matrix* matrix3 = sum_matrix(matrix1, matrix2);
    // Matrix* matrix4 = mult_matrix(matrix1, matrix2);
    // Matrix* matrix5 = transponate_matrix(matrix1);
    // Matrix* matrix6 = matrix_linear_combination(matrix1, 3, 2, elem);

    // print_matrix_equality(matrix1, matrix2, matrix3, "+");
    // print_matrix_equality(matrix1, matrix2, matrix4, "x");
    // print_matrix_transition(matrix1, matrix5);
    // print_matrix_transition(matrix1, matrix6);

    // return 0;
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
                
                Element elem = create_float_elem();
                *(float*)elem.number = coeff_val;
                
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


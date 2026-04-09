#ifndef FUNC_H
#define FUNC_H

#include "element.h"
#include "matrix.h"

void clear_buffer(void);
int read_int(const char* input, int* output);
const char* format_matrix(int rows, int cols, const TypeElement* type, const char* matrix_data);
int max(int num1, int num2);
int min(int num1, int num2);
int start();

#endif

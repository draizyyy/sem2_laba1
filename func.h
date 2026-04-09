#ifndef FUNC_H
#define FUNC_H

#include "element.h"
#include "matrix.h"

void clear_buffer(void);
int read_int( char* input, int* output);
 char* format_matrix(int rows, int cols,  TypeElement* type,  char* matrix_data);
int max(int num1, int num2);
int min(int num1, int num2);
int start();

#endif

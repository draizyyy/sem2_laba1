#ifndef ARRAY_H
#define ARRAY_H

#include "element.h"

struct TypeArray;

typedef struct {
    Element* data;
    unsigned int size;
    const struct TypeArray* type_array;
} Array;

typedef struct TypeArray {
    Array* (*create)();
    Array* (*create_size)(int size);
    int (*add)(Array* array, Element* element);
    Element* (*get)(Array* array, int index);
    int (*set)(Array* array, int index, Element* elem);
    int (*destroy)(Array* array);
} TypeArray;

Array* create_array_element();
Array* create_array_size_element(int size);
int add_element_to_array(Array* array, Element* elem);
Element* get_element_by_index(Array* array, int index);
int set_element_by_index(Array* array, int index, Element* elem);
int destroy_array(Array* array);
const TypeElement* get_array_type(Array* array);

#endif
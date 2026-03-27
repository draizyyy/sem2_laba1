#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "element.h"

const TypeArray ElementArray = {
    .create = create_array_element,
    .create_size = create_array_size_element,
    .add = add_element_to_array,
    .get = get_element_by_index,
    .destroy = destroy_array
};

Array* create_array_element() {
    Array* array = malloc(sizeof(Array));
    if (array == NULL) return NULL;
    Element *start = malloc(sizeof(Element));

    if (start == NULL) {
        free(array);
        return NULL;
    }

    array->data = start;
    array->size = 0;

    return array;
}

ElementType get_array_type(Array* array) {
    if (array == NULL || array->size == 0) return TYPE_NONE;
    return get_elem_type(get_element_by_index(array, 0));
}

Array* create_array_size_element(int size) {
    if (size < 0) return NULL;
    Array* array = malloc(sizeof(Array));
    if (array == NULL) return NULL;
    
    Element *start = NULL;
    if (size > 0) {
        start = malloc(sizeof(Element) * size);
        if (start == NULL) {
            free(array);
            return NULL;
        }
        for (int i = 0; i < size; i++) {
            start[i].number = NULL;
            start[i].type_element = NULL;
            start[i].type = TYPE_NONE;
            start[i].size = 0;
        }
    }
    
    array->data = start;
    array->size = size;

    return array;
}

int init_int_array(Array* array) {
    if (array == NULL) return 0;
    for (unsigned int i = 0; i < array->size; i++) {
        set_element_by_index(array, i, create("int"));
    }
    return 1;
}

int init_float_array(Array* array) {
    if (array == NULL) return 0;
    for (unsigned int i = 0; i < array->size; i++) {
        set_element_by_index(array, i, create("float"));
    }
    return 1;
}

int add_element_to_array(Array* array, Element* element) {
    if (array == NULL || element == NULL) return 0;
    Element *new_ptr;

    new_ptr = realloc(array->data, sizeof(Element) * (array->size + 1));
    
    if (new_ptr == NULL) {
        return 0; 
    }
    
    array->data = new_ptr;
    
    int index = array->size;
    
    array->data[index] = *element;
    array->size++; 
    return 1; 
}

Element* get_element_by_index(Array* array, int index) {
    if (array == NULL || index < 0 || (unsigned)index >= array->size) return NULL;
    return &array->data[index];
}

int set_element_by_index(Array* array, int index, Element* elem) {
    if (array == NULL || elem == NULL || (unsigned)index >= array->size) {
        return 0;
    }
    array->data[index] = *elem;
    return 1;
}

int destroy_array(Array* array) {
    if (array == NULL) {
        return 0;
    }

    if (array->data != NULL && array->size > 0) {
        for (unsigned int i = 0; i < array->size; i++) {
            if (array->data[i].number != NULL) {
                free(array->data[i].number);
                array->data[i].number = NULL;
            }
        }
        free(array->data);
        array->data = NULL;
    }

    free(array);
    return 1;
}
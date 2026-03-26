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
    Element *start = malloc(sizeof(Element));

    if (start == NULL) {
        return NULL;
    }

    array->data = start;
    array->size = 0;

    return array;
}

ElementType get_array_type(Array* array) {
    if (array->size > 0) {
        return get_elem_type(get_element_by_index(array, 0));
    }
    return TYPE_NONE;
}

Array* create_array_size_element(int size) {
    Array* array = malloc(sizeof(Array));
    Element *start = malloc(sizeof(Element) * size);

    if (start == NULL) {
        return NULL;
    }
    
    array->data = start;
    array->size = size;

    return array;
}

int init_int_array(Array* array) {
    for (unsigned int i = 0; i < array->size; i++) {
        set_element_by_index(array, i, create("int"));
    }
    return 1;
}

int init_float_array(Array* array) {
    for (unsigned int i = 0; i < array->size; i++) {
        set_element_by_index(array, i, create("float"));
    }
    return 1;
}

int add_element_to_array(Array* array, Element* element) {
    Element *new_ptr;

    new_ptr = realloc(array->data, sizeof(Element) * (array->size + 1));
    
    if (new_ptr == NULL) {
        return 0; 
    }
    
    array->data = new_ptr;
    
    int index = array->size;
    
    array->data[index-1] = *element;

    new_ptr[index].number = malloc(sizeof(Element)); 

    array->size++; 
    return 1; 
}

Element* get_element_by_index(Array* array, int index) {
    return &array->data[index];
}

int set_element_by_index(Array* array, int index, Element* elem) {
    if ((unsigned) index < array->size) {
        array->data[index] = *elem;
        // free(elem);
        return 1;
    }
    return 0;
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


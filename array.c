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

// const TypeArray MatrixArray = {
//     .create = create_array_matrix,
//     .create_size = create_array_size_matrix,
//     .add = add_matrix_to_array
// };

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

// Array* add_element_to_array(Array* array, Element* elem) {
//     Array *new_ptr;

//     // сделать структуру гду будет массив и интерфейс для управления им. Проверки
//     // максимум баллов за библу для интерфейса

//     // сделать вот такую штуку чтобы вызывать сразу print(elem)
    
//     new_ptr = realloc(array->data, sizeof(Element) * (array->size+1));
//     if (new_ptr == NULL) {
//         return 0;
//     }

//     int index = array->size;

//     new_ptr[index].number = malloc(sizeof(new_ptr[index].type_info));

//     if (new_ptr[index].number == NULL) {
//         return 0;
//     }
//     array->size++;
//     return new_ptr;
// }

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
        return 1;
    }
    return 0;
}

int destroy_array(Array* array) {
    for (unsigned int i = 0; i < array->size; i++) {
        if(destroy(get_element_by_index(array, i)) != 1) {
            return 0;
        }
    }
    return 1;
}

// Array* create_array_matrix() {
//     Array* array = malloc(sizeof(Array));
//     Matrix *start = malloc(sizeof(Matrix));

//     if (start == NULL) {
//         return NULL;
//     }

//     array->data = start;
//     array->size = 0;

//     return start;
// }

// Array* create_array_size_matrix(int size) {
//     Element *start = malloc(sizeof(Element) * size);

//     if (start == NULL) {
//         return NULL;
//     }

//     return start;
// }

// int add_matrix_to_array(Array* array, Matrix* matrix) {
//     Matrix *new_ptr;

//     // сделать структуру гду будет массив и интерфейс для управления им. Проверки
//     // максимум баллов за библу для интерфейса

//     // сделать вот такую штуку чтобы вызывать сразу print(elem)
    
//     new_ptr = realloc(array->data, sizeof(Matrix) * (array->size+1));
//     if (new_ptr == NULL) {
//         return 0;
//     }

//     int index = array->size;

//     new_ptr[index].number = malloc(sizeof(new_ptr[index].type_info));
//     new_ptr

//     if (new_ptr[index].number == NULL) {
//         return 0;
//     }
//     array->size++;
//     return new_ptr;
// }


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "element.h"

const TypeElement IntType = {
    .scan = scan_int,
    .print = print_int,
    .compare = compare_int,
    .multiply = mult_int,
    .sum = sum_int,
    .create = create_int_elem,
    .create_null = create_null_elem_int,
    .destroy = destroy_elem,
    .get_number = get_int_number_elem,
    .get_elem_type = get_elem_type
};

const TypeElement FloatType = {
    .scan = scan_float,
    .print = print_float,
    .compare = compare_float,
    .multiply = mult_float,
    .sum = sum_float,
    .create = create_float_elem,
    .create_null = create_null_elem_float,
    .destroy = destroy_elem,
    .get_number = get_float_number_elem,
    .get_elem_type = get_elem_type
};

int scan_int(const Element* element, const char* str) {
    int value;
    if (sscanf(str, "%d", &value) != 1) {
        return -1; 
    }
    *(int*)element->number = value;
    return 0;
}

int scan_float(const Element* element, const char* str) {
    float value;
    if (sscanf(str, "%g", &value) != 1) {
        return -1;
    }
    *(float*)element->number = value;
    return 0;
}

char* print_int(const Element* element) {
    if (element == NULL || element->number == NULL) {
        return NULL;
    }
    
    char* str = malloc(32 * sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    
    snprintf(str, 32, "%-5d", *(int*)element->number);  
    return str;
}

char* print_float(const Element* element) {
    if (element == NULL || element->number == NULL) {
        return NULL;
    }
    
    char* str = malloc(32 * sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    
    snprintf(str, 32, "%-5g", *(float*)element->number);
    return str;
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

// int destroy_elem(Element* elem) {
//     if (elem == NULL) {
//         return 0;
//     }

//     // if (elem->type_element != NULL) {
//     //     free(elem->type_element);
//     //     elem->type_element = NULL;
//     // }

//     if (elem->number != NULL) {
//         free(elem->number);
//         elem->number = NULL;
//     }

//     free(elem);

//     return 1;
// }

int destroy_elem(Element* elem) {
    if (elem == NULL) {
        return 0; 
    }

    if (elem->number != NULL) {
        free(elem->number);
        elem->number = NULL; 
    }
    free(elem);

    return 1;
}

Element* create_int_elem() {
    Element* elem = malloc(sizeof(Element));
    elem->size = sizeof(int);
    elem->type_element = &IntType;
    elem->type = TYPE_INT;

    elem->number = malloc(elem->size);
    
    if (elem->number == NULL) {
        return NULL;
    }

    return elem;
}

Element* create_float_elem() {
    Element* elem = malloc(sizeof(Element));
    elem->size = sizeof(float);
    elem->type_element = &FloatType;
    elem->type = TYPE_FLOAT;

    elem->number = malloc(elem->size);
    if (elem->number == NULL) {
        return NULL;
    }

    return elem;
}

Element* create_null_elem_int() {
    Element* elem = malloc(sizeof(Element));
    elem->size = sizeof(int);
    elem->type_element = &IntType;
    elem->type = TYPE_INT;

    elem->number = malloc(elem->size);
    if (elem->number == NULL) {
        return elem;
    }

    *(int*)elem->number = 0;

    return elem;
}

Element* create_null_elem_float() {
    Element* elem = malloc(sizeof(Element));
    elem->size = sizeof(float);
    elem->type_element = &FloatType;
    elem->type = TYPE_FLOAT;

    elem->number = malloc(elem->size);
    if (elem->number == NULL) {
        return elem;
    }

    *(float*)elem->number = 0.0f;

    return elem;
}

Element* sum_int(const Element* element1, const Element* element2) {
    int num1 = *(const int*)(*element1).number;
    int num2 = *(const int*)(*element2).number;

    Element* new_elem = create("int");

    *(int*)new_elem->number = num1 + num2;

    return new_elem;
}

Element* sum_float(const Element* element1, const Element* element2) {
    float num1 = *(const float*)(*element1).number;
    float num2 = *(const float*)(*element2).number;

    Element* new_elem = create("float");

    *(float*)new_elem->number = num1 + num2;

    return new_elem;
}

int scan(const Element* elem, const char* str) {
    return elem->type_element->scan(elem, str);
}

char* print(const Element* elem) {
    return elem->type_element->print(elem);
}

void* get_int_number_elem(Element* elem) {
    return (int*)elem->number;
}

void* get_float_number_elem(Element* elem) {
    return (float*)elem->number;
}

int get_int_number(Element* elem) {
    if (elem == NULL || elem->type_element == NULL || elem->number == NULL) {
        return 0;
    }
    
    if (elem->type == TYPE_INT) {
        return *(int*)elem->type_element->get_number(elem);
    }
    
    return 0;
}

float get_float_number(Element* elem) {
    if (elem == NULL || elem->type_element == NULL || elem->number == NULL) {
        return 0;
    }
    
    if (elem->type == TYPE_FLOAT) {
        return *(float*)elem->type_element->get_number(elem);
    }
    
    return 0;
}

ElementType get_elem_type(Element* elem) {
    return elem->type;
}

int set_int_number(Element* elem, int num) {
    *(int*)elem->number = num;
    return 1;
}

int set_float_number(Element* elem, float num) {
    *(float*)elem->number = num;
    return 1;
}

int destroy(Element* elem) {
    return elem->type_element->destroy(elem);
}

int compare(const Element* left, const Element* right) {
    return left->type_element->compare(left, right);
}

Element* sum(const Element* left, const Element* right) {
    return left->type_element->sum(left, right);
}

Element* multiply(const Element* left, const Element* right) {
    return left->type_element->multiply(left, right);
}

Element* create(char* type) {
    if (strcmp(type, "int") == 0) {
        return create_int_elem();
    } else if (strcmp(type, "float") == 0) {
        return create_float_elem();
    } else {
        return NULL; 
    }
}

Element* create_null(char* type) {
    if (strcmp(type, "int") == 0) {
        return create_null_elem_int();
    } else if (strcmp(type, "float") == 0) {
        return create_null_elem_float();
    } else {
        return NULL;  
    }
}


Element* mult_int(const Element* element1, const Element* element2) {
    int num1 = *(const int*)(*element1).number;
    int num2 = *(const int*)(*element2).number;

    Element *new_elem = create("int");

    *(int*)new_elem->number = num1 * num2;

    return new_elem;
}

Element* mult_float(const Element* element1, const Element* element2) {
    float num1 = *(const float*)(*element1).number;
    float num2 = *(const float*)(*element2).number;

    Element* new_elem = create("float");

    *(float*)new_elem->number = num1 * num2;

    return new_elem;
}

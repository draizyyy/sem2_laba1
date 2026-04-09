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
    .set_number = NULL,
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
    .set_number = NULL,
};

int scan_int(const Element* element, const char* str) {
    if (element == NULL || element->number == NULL || str == NULL) return -1;
    int value;
    if (sscanf(str, "%d", &value) != 1) return -1; 
    *(int*)element->number = value;
    return 0;
}

int scan_float(const Element* element, const char* str) {
    if (element == NULL || element->number == NULL || str == NULL) return -1;
    float value;
    if (sscanf(str, "%g", &value) != 1) return -1;
    *(float*)element->number = value;
    return 0;
}

char* print_int(const Element* element) {
    if (element == NULL || element->number == NULL) return NULL;
    char* str = malloc(32 * sizeof(char));
    if (str == NULL) return NULL;
    snprintf(str, 32, "%-5d", *(int*)element->number);  
    return str;
}

char* print_float(const Element* element) {
    if (element == NULL || element->number == NULL) return NULL;
    char* str = malloc(32 * sizeof(char));
    if (str == NULL) return NULL;
    snprintf(str, 32, "%-5g", *(float*)element->number);
    return str;
}

int compare_int(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return 0;
    int num1 = *(const int*)(element1->number);
    int num2 = *(const int*)(element2->number);
    return num1 == num2;
}

int compare_float(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return 0;
    float num1 = *(const float*)(element1->number);
    float num2 = *(const float*)(element2->number);
    return num1 == num2;
}

int destroy_elem(Element* elem) {
    if (elem == NULL) return 0;
    if (elem->number != NULL) {
        free(elem->number);
        elem->number = NULL; 
    }
    free(elem);
    return 1;
}

Element* create_int_elem() {
    Element* elem = malloc(sizeof(Element));
    if (elem == NULL) return NULL;
    elem->size = sizeof(int);
    elem->type_element = &IntType;
    elem->number = malloc(elem->size);
    if (elem->number == NULL) {
        free(elem);
        return NULL;
    }
    return elem;
}

Element* create_float_elem() {
    Element* elem = malloc(sizeof(Element));
    if (elem == NULL) return NULL;
    elem->size = sizeof(float);
    elem->type_element = &FloatType;
    elem->number = malloc(elem->size);
    if (elem->number == NULL) {
        free(elem);
        return NULL;
    }
    return elem;
}

Element* create_null_elem_int() {
    Element* elem = create_int_elem();
    if (elem == NULL) return NULL;
    *(int*)elem->number = 0;
    return elem;
}

Element* create_null_elem_float() {
    Element* elem = create_float_elem();
    if (elem == NULL) return NULL;
    *(float*)elem->number = 0.0f;
    return elem;
}

Element* sum_int(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return NULL;
    int num1 = *(const int*)(element1->number);
    int num2 = *(const int*)(element2->number);
    Element* new_elem = create((char*)"int");
    if (new_elem == NULL) return NULL;
    *(int*)new_elem->number = num1 + num2;
    return new_elem;
}

Element* sum_float(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return NULL;
    float num1 = *(const float*)(element1->number);
    float num2 = *(const float*)(element2->number);
    Element* new_elem = create((char*)"float");
    if (new_elem == NULL) return NULL;
    *(float*)new_elem->number = num1 + num2;
    return new_elem;
}

int scan(const Element* elem, const char* str) {
    if (elem == NULL || elem->type_element == NULL) return -1;
    return elem->type_element->scan(elem, str);
}

char* print(const Element* elem) {
    if (elem == NULL || elem->type_element == NULL) return NULL;
    return elem->type_element->print(elem);
}

void* get_int_number_elem(Element* elem) {
    if (elem == NULL) return NULL;
    return (int*)elem->number;
}

void* get_float_number_elem(Element* elem) {
    if (elem == NULL) return NULL;
    return (float*)elem->number;
}

int get_int_number(Element* elem) {
    if (elem == NULL || elem->type_element == NULL || elem->number == NULL) return 0;
    if (elem->type_element == &IntType) return *(int*)elem->type_element->get_number(elem);
    return 0;
}

float get_float_number(Element* elem) {
    if (elem == NULL || elem->type_element == NULL || elem->number == NULL) return 0;
    if (elem->type_element == &FloatType) return *(float*)elem->type_element->get_number(elem);
    return 0;
}

int set_int_number(Element* elem, int num) {
    if (elem == NULL || elem->number == NULL) return 0;
    *(int*)elem->number = num;
    return 1;
}

int set_float_number(Element* elem, float num) {
    if (elem == NULL || elem->number == NULL) return 0;
    *(float*)elem->number = num;
    return 1;
}

int destroy(Element* elem) {
    if (elem == NULL || elem->type_element == NULL) return 0;
    return elem->type_element->destroy(elem);
}

int compare(const Element* left, const Element* right) {
    if (left == NULL || right == NULL || left->type_element == NULL) return 0;
    return left->type_element->compare(left, right);
}

Element* sum(const Element* left, const Element* right) {
    if (left == NULL || right == NULL || left->type_element == NULL) return NULL;
    return left->type_element->sum(left, right);
}

Element* multiply(const Element* left, const Element* right) {
    if (left == NULL || right == NULL || left->type_element == NULL) return NULL;
    return left->type_element->multiply(left, right);
}

Element* create(char* type) {
    if (type == NULL) return NULL;
    if (strcmp(type, "int") == 0) return create_int_elem();
    if (strcmp(type, "float") == 0) return create_float_elem();
    return NULL; 
}

Element* create_null(char* type) {
    if (type == NULL) return NULL;
    if (strcmp(type, "int") == 0) return create_null_elem_int();
    if (strcmp(type, "float") == 0) return create_null_elem_float();
    return NULL;  
}

Element* mult_int(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return NULL;
    int num1 = *(const int*)(element1->number);
    int num2 = *(const int*)(element2->number);
    Element* new_elem = create((char*)"int");
    if (new_elem == NULL) return NULL;
    *(int*)new_elem->number = num1 * num2;
    return new_elem;
}

Element* mult_float(const Element* element1, const Element* element2) {
    if (element1 == NULL || element2 == NULL || element1->number == NULL || element2->number == NULL) return NULL;
    float num1 = *(const float*)(element1->number);
    float num2 = *(const float*)(element2->number);
    Element* new_elem = create((char*)"float");
    if (new_elem == NULL) return NULL;
    *(float*)new_elem->number = num1 * num2;
    return new_elem;
}
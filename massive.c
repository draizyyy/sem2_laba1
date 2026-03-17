#include <stdio.h>
#include <stdlib.h>
#include "func.h"

Element *create_massive() {
    Element *start = malloc(sizeof(Element));

    if (start == NULL) {
        return NULL;
    }

    return start;
}

Element *create_massive_size(int size) {
    Element *start = malloc(sizeof(Element) * size);

    if (start == NULL) {
        return NULL;
    }

    return start;
}

Element *add_element(Element *start, int *len) {
    Element *new_ptr;

    // сделать структуру гду будет массив и интерфейс для управления им. Проверки
    // максимум баллов за библу для интерфейса

    // сделать вот такую штуку чтобы вызывать сразу print(elem)
    
Element sum(const Element* left, const Element* right) {
    return left->type_info->sum(left, right);
}


    new_ptr = realloc(start, sizeof(Element) * (*len+1));
    if (new_ptr == NULL) {
        return NULL;
    }
    int index = *len;

    new_ptr[index].number = malloc(sizeof(new_ptr[index].type_info));

    if (new_ptr[index].number == NULL) {
        return NULL;
    }
    (*len)++;
    return new_ptr;
}

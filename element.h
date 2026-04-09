#ifndef ELEMENT_H
#define ELEMENT_H

struct TypeElement;

typedef struct {
    unsigned int size;
    void* number;
     struct TypeElement* type_element;
} Element;

typedef struct TypeElement {
    int (*scan)( Element*,  char* str);
    char* (*print)( Element*);
    int (*compare)( Element*,  Element*);
    Element* (*sum)( Element*,  Element*);
    Element* (*multiply)( Element*,  Element*);
    Element* (*create)();
    Element* (*create_null)();
    int (*destroy)(Element* elem);
    void* (*get_number)(Element* elem);
    int (*set_number)(Element* elem, void* number);
} TypeElement;

extern  TypeElement IntType;
extern  TypeElement FloatType;

int scan_int( Element* element,  char* str);
int scan_float( Element* element,  char* str);
char* print_int( Element* element);
char* print_float( Element* element);
int destroy_elem (Element* elem);
Element* create_int_elem();
Element* create_float_elem();
Element* create_null_elem_int();
Element* create_null_elem_float();
int compare_int( Element* element1,  Element* element2);
int compare_float( Element* element1,  Element* element2);
Element* mult_int( Element* element1,  Element* element2);
Element* mult_float( Element* element1,  Element* element2);
Element* sum_int( Element* element1,  Element* element2);
Element* sum_float( Element* element1,  Element* element2);
int set_int_number(Element* element, int number);
int set_float_number(Element* element, float number);
void* get_int_number_elem(Element* elem);
void* get_float_number_elem(Element* elem);
int get_int_number(Element* elem);
float get_float_number(Element* elem);
int scan( Element* elem,  char* str);
char* print( Element* elem);
int destroy(Element* elem);
int compare( Element* left,  Element* right);
Element* sum( Element* left,  Element* right);
Element* multiply( Element* left,  Element* right);
Element* create(char* type);
Element* create_null(char* type);

#endif
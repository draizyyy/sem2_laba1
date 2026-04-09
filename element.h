#ifndef ELEMENT_H
#define ELEMENT_H

struct TypeElement;

typedef struct {
    unsigned int size;
    void* number;
    const struct TypeElement* type_element;
} Element;

typedef struct TypeElement {
    int (*scan)(const Element*, const char* str);
    char* (*print)(const Element*);
    int (*compare)(const Element*, const Element*);
    Element* (*sum)(const Element*, const Element*);
    Element* (*multiply)(const Element*, const Element*);
    Element* (*create)();
    Element* (*create_null)();
    int (*destroy)(Element* elem);
    void* (*get_number)(Element* elem);
    int (*set_number)(Element* elem, void* number);
} TypeElement;

extern const TypeElement IntType;
extern const TypeElement FloatType;

int scan_int(const Element* element, const char* str);
int scan_float(const Element* element, const char* str);
char* print_int(const Element* element);
char* print_float(const Element* element);
int destroy_elem (Element* elem);
Element* create_int_elem();
Element* create_float_elem();
Element* create_null_elem_int();
Element* create_null_elem_float();
int compare_int(const Element* element1, const Element* element2);
int compare_float(const Element* element1, const Element* element2);
Element* mult_int(const Element* element1, const Element* element2);
Element* mult_float(const Element* element1, const Element* element2);
Element* sum_int(const Element* element1, const Element* element2);
Element* sum_float(const Element* element1, const Element* element2);
int set_int_number(Element* element, int number);
int set_float_number(Element* element, float number);
void* get_int_number_elem(Element* elem);
void* get_float_number_elem(Element* elem);
int get_int_number(Element* elem);
float get_float_number(Element* elem);
int scan(const Element* elem, const char* str);
char* print(const Element* elem);
int destroy(Element* elem);
int compare(const Element* left, const Element* right);
Element* sum(const Element* left, const Element* right);
Element* multiply(const Element* left, const Element* right);
Element* create(char* type);
Element* create_null(char* type);

#endif
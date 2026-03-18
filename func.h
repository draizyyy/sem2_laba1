#ifndef FUNC_H
#define FUNC_H

struct TypeInfo;

typedef struct {
    unsigned int size;
    void* number;
    const struct TypeInfo* type_info;
} Element;

typedef struct {
    Element* massive;
    int row, col;
} Matrix;

typedef struct TypeInfo {
    void (*scan)(const Element*);
    void (*print)(const Element*);

    // Element (*scan)(const char*);
    // и принт такой же
    void (*destroy)(Element* elem);
    int (*compare)(const Element*, const Element*);
    Element (*sum)(const Element*, const Element*);
    Element (*multiply)(const Element*, const Element*);
    Element (*create)();
    Element (*create_null_elem)();
} TypeInfo;

     
void scan_int(const Element* element);
void scan_float(const Element* element);
void print_int(const Element* element);
void print_float(const Element* element);
void destroy_elem (Element* elem);
Element create_int_elem();
Element create_float_elem();
Element create_null_elem_int();
Element create_null_elem_float();
int compare_int(const Element* element1, const Element* element2);
int compare_float(const Element* element1, const Element* element2);
Element mult_int(const Element* element1, const Element* element2);
Element mult_float(const Element* element1, const Element* element2);
Element sum_int(const Element* element1, const Element* element2);
Element sum_float(const Element* element1, const Element* element2);

int test1();
int test2();
int test3();
int test4();
int test5();
int test5();
int test6();
int test7();
int test8();
int test9();
int test10();
int test11();
int test12();
int test13();
int test14();
int test15();

int start();

#endif

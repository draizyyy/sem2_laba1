#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <climits>
#include <cfloat>

extern "C" {
    #include "element.h"
    #include "array.h"
    #include "matrix.h"
    #include "func.h"
}

static int global_max(int a, int b) { return max(a, b); }
static int global_min(int a, int b) { return min(a, b); }

// ============================================================================
//                           ELEMENT TESTS (INT)
// ============================================================================

TEST(ElementTest, CreateInt) {
    Element* elem = create((char*)"int");
    EXPECT_NE(elem, nullptr);
    EXPECT_NE(elem->number, nullptr);
    EXPECT_EQ(elem->size, sizeof(int));
    EXPECT_EQ(elem->type, TYPE_INT);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetZero) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, 0), 1);
    EXPECT_EQ(get_int_number(elem), 0);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetNegative) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, -42), 1);
    EXPECT_EQ(get_int_number(elem), -42);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetMaxInt) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, INT_MAX), 1);
    EXPECT_EQ(get_int_number(elem), INT_MAX);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetMinInt) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, INT_MIN), 1);
    EXPECT_EQ(get_int_number(elem), INT_MIN);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetLargePositive) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, 1000000), 1);
    EXPECT_EQ(get_int_number(elem), 1000000);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetLargeNegative) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, -1000000), 1);
    EXPECT_EQ(get_int_number(elem), -1000000);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_GetNullPointer) {
    Element* elem = create((char*)"int");
    if (elem->number) free(elem->number);
    elem->number = nullptr;
    EXPECT_EQ(get_int_number(elem), 0);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintZero) {
    Element* elem = create((char*)"int");
    set_int_number(elem, 0);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    EXPECT_TRUE(strstr(str, "0") != nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintNegative) {
    Element* elem = create((char*)"int");
    set_int_number(elem, -123);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    EXPECT_TRUE(strstr(str, "-123") != nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintMaxInt) {
    Element* elem = create((char*)"int");
    set_int_number(elem, INT_MAX);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintNullElem) {
    EXPECT_EQ(print(nullptr), nullptr);
}

TEST(ElementTest, CreateInt_PrintNullNumber) {
    Element* elem = create((char*)"int");
    if (elem->number) free(elem->number);
    elem->number = nullptr;
    EXPECT_EQ(print(elem), nullptr);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidPositive) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "42"), 0);
    EXPECT_EQ(get_int_number(elem), 42);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidNegative) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "-42"), 0);
    EXPECT_EQ(get_int_number(elem), -42);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidZero) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "0"), 0);
    EXPECT_EQ(get_int_number(elem), 0);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanInvalidLetters) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "abc"), -1);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanInvalidMixed) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "12abc"), 0); 
    EXPECT_EQ(get_int_number(elem), 12);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanEmpty) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, ""), -1);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_CompareEqualZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 0);
    set_int_number(b, 0);
    EXPECT_EQ(compare_int(a, b), 1);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareEqualNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, -100);
    set_int_number(b, -100);
    EXPECT_EQ(compare_int(a, b), 1);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNotEqualPositive) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 10);
    set_int_number(b, 20);
    EXPECT_EQ(compare_int(a, b), 0);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNullFirst) {
    Element* b = create((char*)"int");
    EXPECT_EQ(compare_int(nullptr, b), 0);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNullSecond) {
    Element* a = create((char*)"int");
    EXPECT_EQ(compare_int(a, nullptr), 0);
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_SumWithZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 42);
    set_int_number(b, 0);
    Element* res = sum_int(a, b);
    EXPECT_EQ(get_int_number(res), 42);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, -10);
    set_int_number(b, -20);
    Element* res = sum_int(a, b);
    EXPECT_EQ(get_int_number(res), -30);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumMixed) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 100);
    set_int_number(b, -30);
    Element* res = sum_int(a, b);
    EXPECT_EQ(get_int_number(res), 70);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumNullFirst) {
    Element* b = create((char*)"int");
    EXPECT_EQ(sum_int(nullptr, b), nullptr);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_SumNullSecond) {
    Element* a = create((char*)"int");
    EXPECT_EQ(sum_int(a, nullptr), nullptr);
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_MultiplyByZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 42);
    set_int_number(b, 0);
    Element* res = mult_int(a, b);
    EXPECT_EQ(get_int_number(res), 0);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyByOne) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 42);
    set_int_number(b, 1);
    Element* res = mult_int(a, b);
    EXPECT_EQ(get_int_number(res), 42);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, -6);
    set_int_number(b, 7);
    Element* res = mult_int(a, b);
    EXPECT_EQ(get_int_number(res), -42);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyBothNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, -6);
    set_int_number(b, -7);
    Element* res = mult_int(a, b);
    EXPECT_EQ(get_int_number(res), 42);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyNullFirst) {
    Element* b = create((char*)"int");
    EXPECT_EQ(mult_int(nullptr, b), nullptr);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_MultiplyNullSecond) {
    Element* a = create((char*)"int");
    EXPECT_EQ(mult_int(a, nullptr), nullptr);
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_DestroyAlreadyNull) {
    EXPECT_EQ(destroy_elem(nullptr), 0);
}

// ============================================================================
//                           ELEMENT TESTS (FLOAT)
// ============================================================================

TEST(ElementTest, CreateFloat) {
    Element* elem = create((char*)"float");
    EXPECT_NE(elem, nullptr);
    EXPECT_NE(elem->number, nullptr);
    EXPECT_EQ(elem->size, sizeof(float));
    EXPECT_EQ(elem->type, TYPE_FLOAT);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetZero) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(set_float_number(elem, 0.0f), 1);
    EXPECT_FLOAT_EQ(get_float_number(elem), 0.0f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetNegative) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(set_float_number(elem, -3.14f), 1);
    EXPECT_FLOAT_EQ(get_float_number(elem), -3.14f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetLarge) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(set_float_number(elem, 1e10f), 1);
    EXPECT_FLOAT_EQ(get_float_number(elem), 1e10f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetSmall) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(set_float_number(elem, 1e-10f), 1);
    EXPECT_FLOAT_EQ(get_float_number(elem), 1e-10f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_PrintZero) {
    Element* elem = create((char*)"float");
    set_float_number(elem, 0.0f);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_PrintNegative) {
    Element* elem = create((char*)"float");
    set_float_number(elem, -2.5f);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanValid) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(scan_float(elem, "3.14"), 0);
    EXPECT_FLOAT_EQ(get_float_number(elem), 3.14f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanScientific) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(scan_float(elem, "1.5e2"), 0);
    EXPECT_FLOAT_EQ(get_float_number(elem), 150.0f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanNegative) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(scan_float(elem, "-2.5"), 0);
    EXPECT_FLOAT_EQ(get_float_number(elem), -2.5f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanInvalid) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(scan_float(elem, "abc"), -1);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_CompareEqual) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, 3.14f);
    set_float_number(b, 3.14f);
    EXPECT_EQ(compare_float(a, b), 1);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateFloat_CompareNotEqual) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, 3.14f);
    set_float_number(b, 3.15f);
    EXPECT_EQ(compare_float(a, b), 0);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateFloat_SumBasic) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, 1.5f);
    set_float_number(b, 2.3f);
    Element* res = sum_float(a, b);
    EXPECT_FLOAT_EQ(get_float_number(res), 3.8f);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_SumNegative) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, -1.5f);
    set_float_number(b, -2.3f);
    Element* res = sum_float(a, b);
    EXPECT_FLOAT_EQ(get_float_number(res), -3.8f);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_MultiplyBasic) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, 2.5f);
    set_float_number(b, 4.0f);
    Element* res = mult_float(a, b);
    EXPECT_FLOAT_EQ(get_float_number(res), 10.0f);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_MultiplyByZero) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    set_float_number(a, 2.5f);
    set_float_number(b, 0.0f);
    Element* res = mult_float(a, b);
    EXPECT_FLOAT_EQ(get_float_number(res), 0.0f);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_DestroyNull) {
    EXPECT_EQ(destroy_elem(nullptr), 0);
}

// ============================================================================
//                           ELEMENT TESTS (CREATE/INVALID)
// ============================================================================

TEST(ElementTest, CreateEmptyString) {
    Element* elem = create((char*)"");
    EXPECT_EQ(elem, nullptr);
}

TEST(ElementTest, CreateNullString) {
    Element* elem = create(nullptr);
    EXPECT_EQ(elem, nullptr);
}

TEST(ElementTest, CreateUnknownType) {
    Element* elem = create((char*)"double");
    EXPECT_EQ(elem, nullptr);
}

TEST(ElementTest, CreateNullElem_Int) {
    Element* elem = create_null((char*)"int");
    EXPECT_NE(elem, nullptr);
    EXPECT_EQ(get_int_number(elem), 0);
    destroy_elem(elem);
}

TEST(ElementTest, CreateNullElem_Float) {
    Element* elem = create_null((char*)"float");
    EXPECT_NE(elem, nullptr);
    EXPECT_FLOAT_EQ(get_float_number(elem), 0.0f);
    destroy_elem(elem);
}

TEST(ElementTest, CreateNullElem_Invalid) {
    Element* elem = create_null((char*)"invalid");
    EXPECT_EQ(elem, nullptr);
}

// ============================================================================
//                           ARRAY TESTS (BASIC)
// ============================================================================

TEST(ArrayTest, CreateArraySize_Zero) {
    Array* arr = create_array_size_element(0);
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ((int)arr->size, 0);
    if (arr->data) free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_One) {
    Array* arr = create_array_size_element(1);
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ((int)arr->size, 1);
    EXPECT_NE(arr->data, nullptr);
    if (arr->data[0].number) free(arr->data[0].number);
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_Large) {
    Array* arr = create_array_size_element(1000);
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ((int)arr->size, 1000);
    EXPECT_NE(arr->data, nullptr);
    
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_NullCheck) {
    Array* arr = create_array_size_element(5);
    EXPECT_NE(arr, nullptr);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
    }
    free(arr->data);
    free(arr);
}

// ============================================================================
//                           ARRAY TESTS (GET/SET)
// ============================================================================

TEST(ArrayTest, GetElementByIndex_First) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    set_element_by_index(arr, 0, create((char*)"int"));
    Element* elem = get_element_by_index(arr, 0);
    EXPECT_NE(elem, nullptr);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetElementByIndex_Last) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    set_element_by_index(arr, 4, create((char*)"int"));
    Element* elem = get_element_by_index(arr, 4);
    EXPECT_NE(elem, nullptr);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetElementByIndex_Middle) {
    Array* arr = create_array_size_element(10);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    set_element_by_index(arr, 5, create((char*)"int"));
    Element* elem = get_element_by_index(arr, 5);
    EXPECT_NE(elem, nullptr);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_ValuePreserved) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    Element* new_elem = create((char*)"int");
    set_int_number(new_elem, 777);
    set_element_by_index(arr, 3, new_elem);
    Element* retrieved = get_element_by_index(arr, 3);
    EXPECT_EQ(get_int_number(retrieved), 777);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_Overwrite) {
    Array* arr = create_array_size_element(3);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, i, create((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i * 10);
    }
    Element* new_elem = create((char*)"int");
    set_int_number(new_elem, 999);
    set_element_by_index(arr, 1, new_elem);
    EXPECT_EQ(get_int_number(get_element_by_index(arr, 1)), 999);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_NegativeIndex) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    Element* new_elem = create((char*)"int");
    int result = set_element_by_index(arr, -1, new_elem);
    EXPECT_EQ(result, 0);
    destroy_elem(new_elem);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_NullArray) {
    Element* new_elem = create((char*)"int");
    int result = set_element_by_index(nullptr, 0, new_elem);
    EXPECT_EQ(result, 0);
    destroy_elem(new_elem);
}

TEST(ArrayTest, SetElementByIndex_NullElem) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    int result = set_element_by_index(arr, 0, nullptr);
    EXPECT_EQ(result, 0);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

// ============================================================================
//                           ARRAY TESTS (TYPE)
// ============================================================================

TEST(ArrayTest, GetArrayType_Empty) {
    Array* arr = create_array_size_element(0);
    EXPECT_EQ(get_array_type(arr), TYPE_NONE);
    if (arr->data) free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetArrayType_Float) {
    Array* arr = create_array_size_element(3);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, i, create((char*)"float"));
    }
    EXPECT_EQ(get_array_type(arr), TYPE_FLOAT);
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetArrayType_NullArray) {
    EXPECT_EQ(get_array_type(nullptr), TYPE_NONE);
}

// ============================================================================
//                           ARRAY TESTS (DESTROY)
// ============================================================================

TEST(ArrayTest, DestroyArray_Null) {
    EXPECT_EQ(destroy_array(nullptr), 0);
}

TEST(ArrayTest, DestroyArray_Empty) {
    Array* arr = create_array_size_element(0);
    EXPECT_EQ(destroy_array(arr), 1);
}

TEST(ArrayTest, DestroyArray_WithIntElements) {
    Array* arr = create_array_size_element(3);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, i, create((char*)"int"));
    }
    EXPECT_EQ(destroy_array(arr), 1);
}

TEST(ArrayTest, DestroyArray_WithFloatElements) {
    Array* arr = create_array_size_element(3);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, i, create((char*)"float"));
    }
    EXPECT_EQ(destroy_array(arr), 1);
}

// ============================================================================
//                           MATRIX TESTS (CREATE)
// ============================================================================

TEST(MatrixTest, CreateMatrix_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 1, 1);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 1);
    EXPECT_EQ(get_cols(m), 1);
    destroy_matrix(m);
}

TEST(MatrixTest, CreateMatrix_1xN) {
    Array* arr = create_array_size_element(5);
    for (int i = 0; i < 5; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 1, 5);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 1);
    EXPECT_EQ(get_cols(m), 5);
    destroy_matrix(m);
}

TEST(MatrixTest, CreateMatrix_Nx1) {
    Array* arr = create_array_size_element(5);
    for (int i = 0; i < 5; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 5, 1);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 5);
    EXPECT_EQ(get_cols(m), 1);
    destroy_matrix(m);
}

TEST(MatrixTest, CreateMatrix_Large) {
    Array* arr = create_array_size_element(100);
    for (int i = 0; i < 100; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 10, 10);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 10);
    EXPECT_EQ(get_cols(m), 10);
    destroy_matrix(m);
}

TEST(MatrixTest, CreateMatrix_NullArray) {
    Matrix* m = create_matrix(nullptr, 3, 3);
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    Array* arr = create_array_size_element(0);
    Matrix* m = create_matrix(arr, 0, 3);
    EXPECT_EQ(m, nullptr);
    if (arr) { if (arr->data) free(arr->data); free(arr); }
}

TEST(MatrixTest, CreateMatrix_ZeroCols) {
    Array* arr = create_array_size_element(0);
    Matrix* m = create_matrix(arr, 3, 0);
    EXPECT_EQ(m, nullptr);
    if (arr) { if (arr->data) free(arr->data); free(arr); }
}

// ============================================================================
//                           MATRIX TESTS (GETTERS)
// ============================================================================

TEST(MatrixTest, GetRowsCols_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 1, 1);
    EXPECT_EQ(get_rows(m), 1);
    EXPECT_EQ(get_cols(m), 1);
    destroy_matrix(m);
}

TEST(MatrixTest, GetRowsCols_5x7) {
    Array* arr = create_array_size_element(35);
    for (int i = 0; i < 35; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 5, 7);
    EXPECT_EQ(get_rows(m), 5);
    EXPECT_EQ(get_cols(m), 7);
    destroy_matrix(m);
}

TEST(MatrixTest, GetRowsCols_NullMatrix) {
    EXPECT_EQ(get_rows(nullptr), 0);
    EXPECT_EQ(get_cols(nullptr), 0);
}

TEST(MatrixTest, GetArray_ReturnsValid) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 2, 2);
    EXPECT_NE(get_array(m), nullptr);
    EXPECT_EQ(get_array(m)->size, 4);
    destroy_matrix(m);
}

TEST(MatrixTest, GetArray_NullMatrix) {
    EXPECT_EQ(get_array(nullptr), nullptr);
}

// ============================================================================
//                           MATRIX TESTS (PRINT)
// ============================================================================

TEST(MatrixTest, PrintMatrix_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(arr, 0), 42);
    Matrix* m = create_matrix(arr, 1, 1);
    char* str = print_matrix(m);
    EXPECT_NE(str, nullptr);
    EXPECT_TRUE(strstr(str, "42") != nullptr);
    free(str);
    destroy_matrix(m);
}

TEST(MatrixTest, PrintMatrix_2x2) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 2, 2);
    char* str = print_matrix(m);
    EXPECT_NE(str, nullptr);
    EXPECT_TRUE(strstr(str, "│") != nullptr);
    free(str);
    destroy_matrix(m);
}

TEST(MatrixTest, PrintMatrix_Float) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"float"));
        set_float_number(get_element_by_index(arr, i), (i + 1) * 0.5f);
    }
    Matrix* m = create_matrix(arr, 2, 2);
    char* str = print_matrix(m);
    EXPECT_NE(str, nullptr);
    free(str);
    destroy_matrix(m);
}

TEST(MatrixTest, PrintMatrix_NullMatrix) {
    EXPECT_EQ(print_matrix(nullptr), nullptr);
}

TEST(MatrixTest, PrintMatrix_MemoryLeakCheck) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i);
    }
    Matrix* m = create_matrix(arr, 2, 2);
    for (int i = 0; i < 10; i++) {
        char* str = print_matrix(m);
        if (str) free(str);
    }
    destroy_matrix(m);
}

// ============================================================================
//                           MATRIX TESTS (SUM)
// ============================================================================

TEST(MatrixTest, SumMatrix_1x1) {
    Array* a1 = create_array_size_element(1);
    Array* a2 = create_array_size_element(1);
    set_element_by_index(a1, 0, create_null((char*)"int"));
    set_element_by_index(a2, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(a1, 0), 5);
    set_int_number(get_element_by_index(a2, 0), 3);
    Matrix* m1 = create_matrix(a1, 1, 1);
    Matrix* m2 = create_matrix(a2, 1, 1);
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(res), 0)), 8);
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(res);
}

TEST(MatrixTest, SumMatrix_Float) {
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(a1, i, create_null((char*)"float"));
        set_element_by_index(a2, i, create_null((char*)"float"));
        set_float_number(get_element_by_index(a1, i), 1.5f);
        set_float_number(get_element_by_index(a2, i), 2.5f);
    }
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_NE(res, nullptr);
    EXPECT_FLOAT_EQ(get_float_number(get_element_by_index(get_array(res), 0)), 4.0f);
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(res);
}

TEST(MatrixTest, SumMatrix_DifferentTypes) {
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    for (int i = 0; i < 4; i++) set_element_by_index(a2, i, create_null((char*)"float"));
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(MatrixTest, SumMatrix_NullFirst) {
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a2, i, create_null((char*)"int"));
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = sum_matrix(nullptr, m2);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m2);
}

TEST(MatrixTest, SumMatrix_NullSecond) {
    Array* a1 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* res = sum_matrix(m1, nullptr);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m1);
}

// ============================================================================
//                           MATRIX TESTS (MULTIPLY)
// ============================================================================

TEST(MatrixTest, MultMatrix_2x2_2x2) {
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(a1, i, create_null((char*)"int"));
        set_element_by_index(a2, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(a1, i), 1);
        set_int_number(get_element_by_index(a2, i), 2);
    }
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = mult_matrix(m1, m2);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(get_rows(res), 2);
    EXPECT_EQ(get_cols(res), 2);
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(res);
}

TEST(MatrixTest, MultMatrix_Incompatible) {
    Array* a1 = create_array_size_element(6);
    Array* a2 = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(a1, i, create_null((char*)"int"));
        set_element_by_index(a2, i, create_null((char*)"int"));
    }
    Matrix* m1 = create_matrix(a1, 2, 3);
    Matrix* m2 = create_matrix(a2, 2, 3); 
    Matrix* res = mult_matrix(m1, m2);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(MatrixTest, MultMatrix_NullFirst) {
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a2, i, create_null((char*)"int"));
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = mult_matrix(nullptr, m2);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m2);
}

TEST(MatrixTest, MultMatrix_NullSecond) {
    Array* a1 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* res = mult_matrix(m1, nullptr);
    EXPECT_EQ(res, nullptr);
    destroy_matrix(m1);
}

// ============================================================================
//                           MATRIX TESTS (TRANSPOSE)
// ============================================================================

TEST(MatrixTest, TransposeMatrix_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(arr, 0), 42);
    Matrix* m = create_matrix(arr, 1, 1);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(get_rows(t), 1);
    EXPECT_EQ(get_cols(t), 1);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(t), 0)), 42);
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_1xN) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 1, 4);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(get_rows(t), 4);
    EXPECT_EQ(get_cols(t), 1);
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Nx1) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 4, 1);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(get_rows(t), 1);
    EXPECT_EQ(get_cols(t), 4);
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Float) {
    Array* arr = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(arr, i, create_null((char*)"float"));
        set_float_number(get_element_by_index(arr, i), (i + 1) * 0.5f);
    }
    Matrix* m = create_matrix(arr, 2, 3);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(get_rows(t), 3);
    EXPECT_EQ(get_cols(t), 2);
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Null) {
    EXPECT_EQ(transponate_matrix(nullptr), nullptr);
}

// ============================================================================
//                           MATRIX TESTS (STRING PARSE)
// ============================================================================

TEST(MatrixTest, StringToMatrix_1x1_Int) {
    const char* input = "1 1 1\n42";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 1);
    EXPECT_EQ(get_cols(m), 1);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(m), 0)), 42);
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_3x3_Int) {
    const char* input = "3 3 1\n1 2 3 4 5 6 7 8 9";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 3);
    EXPECT_EQ(get_cols(m), 3);
    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(get_int_number(get_element_by_index(get_array(m), i)), i + 1);
    }
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_2x2_Float) {
    const char* input = "2 2 2\n1.1 2.2 3.3 4.4";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_FLOAT_EQ(get_float_number(get_element_by_index(get_array(m), 0)), 1.1f);
    EXPECT_FLOAT_EQ(get_float_number(get_element_by_index(get_array(m), 3)), 4.4f);
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_InvalidHeader) {
    Matrix* m = string_to_matrix("abc 2 1\n1 2");
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_ZeroRows) {
    Matrix* m = string_to_matrix("0 2 1\n");
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_ZeroCols) {
    Matrix* m = string_to_matrix("2 0 1\n1 2");
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_InvalidType) {
    Matrix* m = string_to_matrix("2 2 3\n1 2 3 4");
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_NotEnoughValues) {
    Matrix* m = string_to_matrix("2 2 1\n1 2 3");
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_NullInput) {
    Matrix* m = string_to_matrix(nullptr);
    EXPECT_EQ(m, nullptr);
}

TEST(MatrixTest, StringToMatrix_EmptyInput) {
    Matrix* m = string_to_matrix("");
    EXPECT_EQ(m, nullptr);
}

// ============================================================================
//                           MATRIX TESTS (DESTROY)
// ============================================================================

TEST(MatrixTest, DestroyMatrix_Null) {
    EXPECT_EQ(destroy_matrix(nullptr), 0);
}

TEST(MatrixTest, DestroyMatrix_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 1, 1);
    EXPECT_EQ(destroy_matrix(m), 1);
}

TEST(MatrixTest, DestroyMatrix_Large) {
    Array* arr = create_array_size_element(100);
    for (int i = 0; i < 100; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 10, 10);
    EXPECT_EQ(destroy_matrix(m), 1);
}

TEST(MatrixTest, DestroyMatrix_MultipleNoLeak) {
    for (int i = 0; i < 10; i++) {
        Array* arr = create_array_size_element(4);
        for (int j = 0; j < 4; j++) set_element_by_index(arr, j, create_null((char*)"int"));
        Matrix* m = create_matrix(arr, 2, 2);
        if (m) destroy_matrix(m);
    }
}

// ============================================================================
//                           HELPER FUNCTION TESTS
// ============================================================================

TEST(HelperTest, Max_Equal) {
    EXPECT_EQ(global_max(5, 5), 5);
}

TEST(HelperTest, Max_Negative) {
    EXPECT_EQ(global_max(-5, -3), -3);
    EXPECT_EQ(global_max(-10, -1), -1);
}

TEST(HelperTest, Max_Large) {
    EXPECT_EQ(global_max(1000000, 999999), 1000000);
}

TEST(HelperTest, Min_Equal) {
    EXPECT_EQ(global_min(5, 5), 5);
}

TEST(HelperTest, Min_Negative) {
    EXPECT_EQ(global_min(-5, -3), -5);
    EXPECT_EQ(global_min(-10, -1), -10);
}

TEST(HelperTest, Min_Large) {
    EXPECT_EQ(global_min(1000000, 999999), 999999);
}

TEST(HelperTest, FormatMatrix_Basic) {
    const char* result = format_matrix(2, 3, 1, "1 2 3 4 5 6");
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(strstr(result, "2 3 1") != nullptr);
    EXPECT_TRUE(strstr(result, "1 2 3 4 5 6") != nullptr);
    free((void*)result);
}

TEST(HelperTest, FormatMatrix_NullData) {
    const char* result = format_matrix(1, 1, 1, nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST(HelperTest, FormatMatrix_ZeroSize) {
    const char* result = format_matrix(0, 0, 1, "");
    EXPECT_NE(result, nullptr);
    free((void*)result);
}

TEST(HelperTest, ClearBuffer_Exists) {
    EXPECT_TRUE(clear_buffer != nullptr);
}

// ============================================================================
//                           INTEGRATION TESTS
// ============================================================================

TEST(IntegrationTest, CreatePrintDestroy) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 2, 2);
    char* str = print_matrix(m);
    if (str) free(str);
    destroy_matrix(m);
}

TEST(IntegrationTest, SumThenPrint) {
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(a1, i, create_null((char*)"int"));
        set_element_by_index(a2, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(a1, i), i);
        set_int_number(get_element_by_index(a2, i), i * 2);
    }
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = sum_matrix(m1, m2);
    if (res) {
        char* str = print_matrix(res);
        if (str) free(str);
        destroy_matrix(res);
    }
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(IntegrationTest, TransposeThenSum) {
    Array* arr = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 2, 3);
    Matrix* t = transponate_matrix(m);
    if (t) {
        Array* arr2 = create_array_size_element(6);
        for (int i = 0; i < 6; i++) set_element_by_index(arr2, i, create_null((char*)"int"));
        Matrix* m2 = create_matrix(arr2, 3, 2);
        Matrix* res = sum_matrix(t, m2);
        if (res) destroy_matrix(res);
        destroy_matrix(m2);
    }
    destroy_matrix(m);
    if (t) destroy_matrix(t);
}

TEST(IntegrationTest, StringParseThenOperate) {
    const char* input1 = "2 2 1\n1 2 3 4";
    const char* input2 = "2 2 1\n5 6 7 8";
    Matrix* m1 = string_to_matrix(input1);
    Matrix* m2 = string_to_matrix(input2);
    if (m1 && m2) {
        Matrix* res = sum_matrix(m1, m2);
        if (res) {
            EXPECT_EQ(get_int_number(get_element_by_index(get_array(res), 0)), 6);
            destroy_matrix(res);
        }
    }
    if (m1) destroy_matrix(m1);
    if (m2) destroy_matrix(m2);
}

// ============================================================================
//                           EDGE CASE TESTS
// ============================================================================

TEST(EdgeCaseTest, Element_OperationsWithZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 0);
    set_int_number(b, 0);
    Element* sum = sum_int(a, b);
    EXPECT_EQ(get_int_number(sum), 0);
    Element* prod = mult_int(a, b);
    EXPECT_EQ(get_int_number(prod), 0);
    destroy_elem(a); destroy_elem(b); destroy_elem(sum); destroy_elem(prod);
}

TEST(EdgeCaseTest, Element_OperationsWithMaxValues) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, INT_MAX / 2);
    set_int_number(b, INT_MAX / 2);
    Element* sum = sum_int(a, b);
    EXPECT_NE(sum, nullptr);
    destroy_elem(a); destroy_elem(b);
    if (sum) destroy_elem(sum);
}

TEST(EdgeCaseTest, Matrix_EmptyStringParse) {
    Matrix* m = string_to_matrix("");
    EXPECT_EQ(m, nullptr);
}

TEST(EdgeCaseTest, Matrix_WhitespaceInString) {
    const char* input = "  2  2  1  \n  1  2  3  4  ";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    if (m) destroy_matrix(m);
}

TEST(EdgeCaseTest, Matrix_NegativeValues) {
    const char* input = "2 2 1\n-1 -2 -3 -4";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(m), 0)), -1);
    if (m) destroy_matrix(m);
}

// ============================================================================
//                           MAIN
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
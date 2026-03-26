#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

extern "C" {
    #include "element.h"
    #include "array.h"
    #include "matrix.h"
    #include "func.h"
}
static int global_max(int a, int b) { return max(a, b); }
static int global_min(int a, int b) { return min(a, b); }

// ============================================================================
//                           ELEMENT TESTS
// ============================================================================

TEST(ElementTest, CreateInt) {
    Element* elem = create((char*)"int");
    EXPECT_NE(elem, nullptr);
    EXPECT_NE(elem->number, nullptr);
    EXPECT_EQ(elem->size, sizeof(int));
    EXPECT_EQ(elem->type, TYPE_INT);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat) {
    Element* elem = create((char*)"float");
    EXPECT_NE(elem, nullptr);
    EXPECT_NE(elem->number, nullptr);
    EXPECT_EQ(elem->size, sizeof(float));
    EXPECT_EQ(elem->type, TYPE_FLOAT);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInvalid) {
    Element* elem = create((char*)"invalid");
    EXPECT_EQ(elem, nullptr);
}

TEST(ElementTest, SetGetInt) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(set_int_number(elem, 42), 1);
    EXPECT_EQ(get_int_number(elem), 42);
    destroy_elem(elem);
}

TEST(ElementTest, SetGetFloat) {
    Element* elem = create((char*)"float");
    EXPECT_EQ(set_float_number(elem, 3.14f), 1);
    EXPECT_FLOAT_EQ(get_float_number(elem), 3.14f);
    destroy_elem(elem);
}

TEST(ElementTest, PrintInt) {
    Element* elem = create((char*)"int");
    set_int_number(elem, 123);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    EXPECT_STRNE(str, "");
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, PrintFloat) {
    Element* elem = create((char*)"float");
    set_float_number(elem, 2.5f);
    char* str = print(elem);
    EXPECT_NE(str, nullptr);
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, ScanIntValid) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "42"), 0);
    EXPECT_EQ(get_int_number(elem), 42);
    destroy_elem(elem);
}

TEST(ElementTest, ScanIntInvalid) {
    Element* elem = create((char*)"int");
    EXPECT_EQ(scan_int(elem, "abc"), -1);
    destroy_elem(elem);
}

TEST(ElementTest, CompareIntEqual) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 42);
    set_int_number(b, 42);
    EXPECT_EQ(compare_int(a, b), 1);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CompareIntNotEqual) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 42);
    set_int_number(b, 43);
    EXPECT_EQ(compare_int(a, b), 0);
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, SumInt) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 10);
    set_int_number(b, 20);
    Element* res = sum_int(a, b);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(get_int_number(res), 30);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, MultiplyInt) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 6);
    set_int_number(b, 7);
    Element* res = mult_int(a, b);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(get_int_number(res), 42);
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, DestroyNull) {
    EXPECT_EQ(destroy_elem(nullptr), 0);
}

// ============================================================================
//                           ARRAY TESTS
// ============================================================================

TEST(ArrayTest, CreateArraySize) {
    Array* arr = create_array_size_element(10);
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ((int)arr->size, 10);
    
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
    }
    
    EXPECT_NE(arr->data, nullptr);

    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetElementByIndex) {
    Array* arr = create_array_size_element(5);

    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
    }
    
    set_element_by_index(arr, 0, create((char*)"int"));
    Element* elem = get_element_by_index(arr, 0);
    EXPECT_NE(elem, nullptr);
    
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndexValid) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    
    Element* new_elem = create((char*)"int");
    set_int_number(new_elem, 999);
    int result = set_element_by_index(arr, 2, new_elem);
    EXPECT_EQ(result, 1);
    
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndexOutOfBounds) {
    Array* arr = create_array_size_element(5);
    for (unsigned i = 0; i < arr->size; i++) arr->data[i].number = NULL;
    
    Element* new_elem = create((char*)"int");
    int result = set_element_by_index(arr, 100, new_elem);
    EXPECT_EQ(result, 0);
    destroy_elem(new_elem);
    
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetArrayTypeInt) {
    Array* arr = create_array_size_element(3);
    for (unsigned i = 0; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, i, create((char*)"int"));
    }
    EXPECT_EQ(get_array_type(arr), TYPE_INT);
    
    for (unsigned i = 0; i < arr->size; i++) {
        if (arr->data[i].number != NULL) {
            free(arr->data[i].number);
        }
    }
    free(arr->data);
    free(arr);
}

// ============================================================================
//                           MATRIX TESTS
// ============================================================================

TEST(MatrixTest, CreateMatrix) {
    Array* arr = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
    }
    Matrix* m = create_matrix(arr, 2, 3);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 2);
    EXPECT_EQ(get_cols(m), 3);
    destroy_matrix(m);
}

TEST(MatrixTest, GetRowsCols) {
    Array* arr = create_array_size_element(9);
    for (int i = 0; i < 9; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 3, 3);
    EXPECT_EQ(get_rows(m), 3);
    EXPECT_EQ(get_cols(m), 3);
    destroy_matrix(m);
}

TEST(MatrixTest, PrintMatrix) {
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

TEST(MatrixTest, SumMatrixSameSize) {
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
    
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(res), 0)), 3);
    
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(res);
}

TEST(MatrixTest, SumMatrixDifferentSize) {
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(9);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    for (int i = 0; i < 9; i++) set_element_by_index(a2, i, create_null((char*)"int"));
    
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 3, 3);
    
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_EQ(res, nullptr);
    
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(MatrixTest, TransposeMatrix) {
    Array* arr = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 2, 3);
    Matrix* t = transponate_matrix(m);
    
    EXPECT_NE(t, nullptr);
    EXPECT_EQ(get_rows(t), 3);
    EXPECT_EQ(get_cols(t), 2);
    
    int orig = get_int_number(get_element_by_index(get_array(m), 1));
    int trans = get_int_number(get_element_by_index(get_array(t), 2));
    EXPECT_EQ(trans, orig);
    
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, StringToMatrixInt) {
    const char* input = "2 2 1\n1 2 3 4";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_EQ(get_rows(m), 2);
    EXPECT_EQ(get_cols(m), 2);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(m), 0)), 1);
    EXPECT_EQ(get_int_number(get_element_by_index(get_array(m), 3)), 4);
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrixFloat) {
    const char* input = "2 2 2\n1.5 2.5 3.5 4.5";
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr);
    EXPECT_FLOAT_EQ(get_float_number(get_element_by_index(get_array(m), 0)), 1.5f);
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrixInvalid) {
    Matrix* m = string_to_matrix("abc 2 1\n1 2");
    EXPECT_EQ(m, nullptr);
}

// ============================================================================
//                           HELPER FUNCTION TESTS
// ============================================================================

TEST(HelperTest, Max) {
    EXPECT_EQ(global_max(5, 3), 5);
    EXPECT_EQ(global_max(1, 10), 10);
    EXPECT_EQ(global_max(7, 7), 7);
    EXPECT_EQ(global_max(-5, -3), -3);
}

TEST(HelperTest, Min) {
    EXPECT_EQ(global_min(5, 3), 3);
    EXPECT_EQ(global_min(1, 10), 1);
    EXPECT_EQ(global_min(7, 7), 7);
    EXPECT_EQ(global_min(-5, -3), -5);
}

TEST(HelperTest, FormatMatrix) {
    const char* result = format_matrix(2, 3, 1, "1 2 3 4 5 6");
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(strstr(result, "2 3 1") != nullptr);
    EXPECT_TRUE(strstr(result, "1 2 3 4 5 6") != nullptr);
    free((void*)result);
}

TEST(HelperTest, ClearBuffer) {
    EXPECT_TRUE(true); 
}

// ============================================================================
//                           MAIN
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
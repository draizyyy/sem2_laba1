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

//ELEMENT TEST INT

TEST(ElementTest, CreateInt) {
    Element* elem = create((char*)"int");
    EXPECT_NE(elem, nullptr) << "Input: create(\"int\"), Expected: not nullptr";
    EXPECT_NE(elem->number, nullptr) << "Input: elem->number, Expected: not nullptr";
    EXPECT_EQ(elem->size, sizeof(int)) << "Expected: " << sizeof(int);
    EXPECT_EQ(elem->type_element, &IntType) << "Expected: &IntType";
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetZero) {
    Element* elem = create((char*)"int");
    int input = 0;
    int expected = 0;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetNegative) {
    Element* elem = create((char*)"int");
    int input = -42;
    int expected = -42;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetMaxInt) {
    Element* elem = create((char*)"int");
    int input = INT_MAX;
    int expected = INT_MAX;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: INT_MAX, Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: INT_MAX, Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetMinInt) {
    Element* elem = create((char*)"int");
    int input = INT_MIN;
    int expected = INT_MIN;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: INT_MIN, Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: INT_MIN, Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetLargePositive) {
    Element* elem = create((char*)"int");
    int input = 1000000;
    int expected = 1000000;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_SetLargeNegative) {
    Element* elem = create((char*)"int");
    int input = -1000000;
    int expected = -1000000;
    EXPECT_EQ(set_int_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_GetNullPointer) {
    Element* elem = create((char*)"int");
    if (elem->number) free(elem->number);
    elem->number = nullptr;
    int expected = 0;
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintZero) {
    Element* elem = create((char*)"int");
    int input = 0;
    set_int_number(elem, input);
    char* str = print(elem);
    EXPECT_NE(str, nullptr) << "Input: " << input << ", Expected: not nullptr";
    bool found = strstr(str, "0") != nullptr;
    EXPECT_TRUE(found) << "Input: " << input << ", Expected substring: 0";
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintNegative) {
    Element* elem = create((char*)"int");
    int input = -123;
    set_int_number(elem, input);
    char* str = print(elem);
    EXPECT_NE(str, nullptr) << "Input: " << input << ", Expected: not nullptr";
    bool found = strstr(str, "-123") != nullptr;
    EXPECT_TRUE(found) << "Input: " << input << ", Expected substring: -123";
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintMaxInt) {
    Element* elem = create((char*)"int");
    set_int_number(elem, INT_MAX);
    char* str = print(elem);
    EXPECT_NE(str, nullptr) << "Input: INT_MAX, Expected: not nullptr";
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_PrintNullElem) {
    char* actual = print(nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr, Expected: nullptr";
}

TEST(ElementTest, CreateInt_PrintNullNumber) {
    Element* elem = create((char*)"int");
    if (elem->number) free(elem->number);
    elem->number = nullptr;
    char* actual = print(elem);
    EXPECT_EQ(actual, nullptr) << "Expected: nullptr";
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidPositive) {
    Element* elem = create((char*)"int");
    char input[] = "42";
    int expected_ret = 0;
    int expected_val = 42;
    int actual_ret = scan_int(elem, input);
    int actual_val = get_int_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidNegative) {
    Element* elem = create((char*)"int");
    char input[] = "-42";
    int expected_ret = 0;
    int expected_val = -42;
    int actual_ret = scan_int(elem, input);
    int actual_val = get_int_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanValidZero) {
    Element* elem = create((char*)"int");
    char input[] = "0";
    int expected_ret = 0;
    int expected_val = 0;
    int actual_ret = scan_int(elem, input);
    int actual_val = get_int_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanInvalidLetters) {
    Element* elem = create((char*)"int");
    char input[] = "abc";
    int expected_ret = -1;
    int actual_ret = scan_int(elem, input);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanInvalidMixed) {
    Element* elem = create((char*)"int");
    char input[] = "12abc";
    int expected_ret = 0;
    int expected_val = 12;
    int actual_ret = scan_int(elem, input);
    int actual_val = get_int_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_ScanEmpty) {
    Element* elem = create((char*)"int");
    char input[] = "";
    int expected_ret = -1;
    int actual_ret = scan_int(elem, input);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    destroy_elem(elem);
}

TEST(ElementTest, CreateInt_CompareEqualZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 0, val_b = 0;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    int expected = 1;
    int actual = compare_int(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " vs " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareEqualNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = -100, val_b = -100;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    int expected = 1;
    int actual = compare_int(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " vs " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNotEqualPositive) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 10, val_b = 20;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    int expected = 0;
    int actual = compare_int(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " vs " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNullFirst) {
    Element* b = create((char*)"int");
    int expected = 0;
    int actual = compare_int(nullptr, b);
    EXPECT_EQ(actual, expected) << "Input: nullptr vs b, Expected: " << expected;
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_CompareNullSecond) {
    Element* a = create((char*)"int");
    int expected = 0;
    int actual = compare_int(a, nullptr);
    EXPECT_EQ(actual, expected) << "Input: a vs nullptr, Expected: " << expected;
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_SumWithZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 42, val_b = 0;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = sum_int(a, b);
    int expected = 42;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = -10, val_b = -20;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = sum_int(a, b);
    int expected = -30;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumMixed) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 100, val_b = -30;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = sum_int(a, b);
    int expected = 70;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_SumNullFirst) {
    Element* b = create((char*)"int");
    Element* actual = sum_int(nullptr, b);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr + b, Expected: nullptr";
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_SumNullSecond) {
    Element* a = create((char*)"int");
    Element* actual = sum_int(a, nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: a + nullptr, Expected: nullptr";
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_MultiplyByZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 42, val_b = 0;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = mult_int(a, b);
    int expected = 0;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyByOne) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = 42, val_b = 1;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = mult_int(a, b);
    int expected = 42;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = -6, val_b = 7;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = mult_int(a, b);
    int expected = -42;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyBothNegative) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    int val_a = -6, val_b = -7;
    set_int_number(a, val_a);
    set_int_number(b, val_b);
    Element* res = mult_int(a, b);
    int expected = 42;
    int actual = get_int_number(res);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateInt_MultiplyNullFirst) {
    Element* b = create((char*)"int");
    Element* actual = mult_int(nullptr, b);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr * b, Expected: nullptr";
    destroy_elem(b);
}

TEST(ElementTest, CreateInt_MultiplyNullSecond) {
    Element* a = create((char*)"int");
    Element* actual = mult_int(a, nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: a * nullptr, Expected: nullptr";
    destroy_elem(a);
}

TEST(ElementTest, CreateInt_DestroyAlreadyNull) {
    int expected = 0;
    int actual = destroy_elem(nullptr);
    EXPECT_EQ(actual, expected) << "Input: nullptr, Expected: " << expected;
}

//ELEMENTS TEST FLOAT

TEST(ElementTest, CreateFloat) {
    Element* elem = create((char*)"float");
    EXPECT_NE(elem, nullptr) << "Input: create(\"float\"), Expected: not nullptr";
    EXPECT_NE(elem->number, nullptr) << "Input: elem->number, Expected: not nullptr";
    EXPECT_EQ(elem->size, sizeof(float)) << "Expected: " << sizeof(float);
    EXPECT_EQ(elem->type_element, &FloatType) << "Expected: &FloatType";
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetZero) {
    Element* elem = create((char*)"float");
    float input = 0.0f;
    float expected = 0.0f;
    EXPECT_EQ(set_float_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    float actual = get_float_number(elem);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetNegative) {
    Element* elem = create((char*)"float");
    float input = -3.14f;
    float expected = -3.14f;
    EXPECT_EQ(set_float_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    float actual = get_float_number(elem);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetLarge) {
    Element* elem = create((char*)"float");
    float input = 1e10f;
    float expected = 1e10f;
    EXPECT_EQ(set_float_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    float actual = get_float_number(elem);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_SetSmall) {
    Element* elem = create((char*)"float");
    float input = 1e-10f;
    float expected = 1e-10f;
    EXPECT_EQ(set_float_number(elem, input), 1) << "Input: " << input << ", Expected return: 1";
    float actual = get_float_number(elem);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << input << ", Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_PrintZero) {
    Element* elem = create((char*)"float");
    set_float_number(elem, 0.0f);
    char* str = print(elem);
    EXPECT_NE(str, nullptr) << "Input: 0.0f, Expected: not nullptr";
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_PrintNegative) {
    Element* elem = create((char*)"float");
    set_float_number(elem, -2.5f);
    char* str = print(elem);
    EXPECT_NE(str, nullptr) << "Input: -2.5f, Expected: not nullptr";
    free(str);
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanValid) {
    Element* elem = create((char*)"float");
    char input[] = "3.14";
    int expected_ret = 0;
    float expected_val = 3.14f;
    int actual_ret = scan_float(elem, input);
    float actual_val = get_float_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_FLOAT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanScientific) {
    Element* elem = create((char*)"float");
    char input[] = "1.5e2";
    int expected_ret = 0;
    float expected_val = 150.0f;
    int actual_ret = scan_float(elem, input);
    float actual_val = get_float_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_FLOAT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanNegative) {
    Element* elem = create((char*)"float");
    char input[] = "-2.5";
    int expected_ret = 0;
    float expected_val = -2.5f;
    int actual_ret = scan_float(elem, input);
    float actual_val = get_float_number(elem);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    EXPECT_FLOAT_EQ(actual_val, expected_val) << "Input: \"" << input << "\", Expected: " << expected_val;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_ScanInvalid) {
    Element* elem = create((char*)"float");
    char input[] = "abc";
    int expected_ret = -1;
    int actual_ret = scan_float(elem, input);
    EXPECT_EQ(actual_ret, expected_ret) << "Input: \"" << input << "\", Expected return: " << expected_ret;
    destroy_elem(elem);
}

TEST(ElementTest, CreateFloat_CompareEqual) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = 3.14f, val_b = 3.14f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    int expected = 1;
    int actual = compare_float(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " vs " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateFloat_CompareNotEqual) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = 3.14f, val_b = 3.15f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    int expected = 0;
    int actual = compare_float(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " vs " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
}

TEST(ElementTest, CreateFloat_SumBasic) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = 1.5f, val_b = 2.3f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    Element* res = sum_float(a, b);
    float expected = 3.8f;
    float actual = get_float_number(res);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_SumNegative) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = -1.5f, val_b = -2.3f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    Element* res = sum_float(a, b);
    float expected = -3.8f;
    float actual = get_float_number(res);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_MultiplyBasic) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = 2.5f, val_b = 4.0f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    Element* res = mult_float(a, b);
    float expected = 10.0f;
    float actual = get_float_number(res);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_MultiplyByZero) {
    Element* a = create((char*)"float");
    Element* b = create((char*)"float");
    float val_a = 2.5f, val_b = 0.0f;
    set_float_number(a, val_a);
    set_float_number(b, val_b);
    Element* res = mult_float(a, b);
    float expected = 0.0f;
    float actual = get_float_number(res);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << val_a << " * " << val_b << ", Expected: " << expected;
    destroy_elem(a);
    destroy_elem(b);
    destroy_elem(res);
}

TEST(ElementTest, CreateFloat_DestroyNull) {
    int expected = 0;
    int actual = destroy_elem(nullptr);
    EXPECT_EQ(actual, expected) << "Input: nullptr, Expected: " << expected;
}

//ELEMENTS TEST CREATE

TEST(ElementTest, CreateEmptyString) {
    Element* actual = create((char*)"");
    EXPECT_EQ(actual, nullptr) << "Input: \"\", Expected: nullptr";
}

TEST(ElementTest, CreateNullString) {
    Element* actual = create(nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr, Expected: nullptr";
}

TEST(ElementTest, CreateUnknownType) {
    Element* actual = create((char*)"double");
    EXPECT_EQ(actual, nullptr) << "Input: \"double\", Expected: nullptr";
}

TEST(ElementTest, CreateNullElem_Int) {
    Element* elem = create_null((char*)"int");
    EXPECT_NE(elem, nullptr) << "Input: \"int\", Expected: not nullptr";
    int expected = 0;
    int actual = get_int_number(elem);
    EXPECT_EQ(actual, expected) << "Input: create_null(\"int\"), Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateNullElem_Float) {
    Element* elem = create_null((char*)"float");
    EXPECT_NE(elem, nullptr) << "Input: \"float\", Expected: not nullptr";
    float expected = 0.0f;
    float actual = get_float_number(elem);
    EXPECT_FLOAT_EQ(actual, expected) << "Input: create_null(\"float\"), Expected: " << expected;
    destroy_elem(elem);
}

TEST(ElementTest, CreateNullElem_Invalid) {
    Element* actual = create_null((char*)"invalid");
    EXPECT_EQ(actual, nullptr) << "Input: \"invalid\", Expected: nullptr";
}

//ARRAY TESTS GENERAL 

TEST(ArrayTest, CreateArraySize_Zero) {
    unsigned int input = 0u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    EXPECT_NE(arr, nullptr) << "Input: " << input << ", Expected: not nullptr";
    unsigned int expected_size = 0u;
    EXPECT_EQ(arr->size, expected_size) << "Input: " << input << ", Expected size: " << expected_size;
    if (arr->data) free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_One) {
    unsigned int input = 1u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    EXPECT_NE(arr, nullptr) << "Input: " << input << ", Expected: not nullptr";
    unsigned int expected_size = 1u;
    EXPECT_EQ(arr->size, expected_size) << "Input: " << input << ", Expected size: " << expected_size;
    EXPECT_NE(arr->data, nullptr) << "Expected: not nullptr";
    if (arr->data[0].number) free(arr->data[0].number);
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_Large) {
    unsigned int input = 1000u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    EXPECT_NE(arr, nullptr) << "Input: " << input << ", Expected: not nullptr";
    unsigned int expected_size = 1000u;
    EXPECT_EQ(arr->size, expected_size) << "Input: " << input << ", Expected size: " << expected_size;
    EXPECT_NE(arr->data, nullptr) << "Expected: not nullptr";
    
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number != NULL) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, CreateArraySize_NullCheck) {
    unsigned int input = 5u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    EXPECT_NE(arr, nullptr) << "Input: " << input << ", Expected: not nullptr";
    for (unsigned int i = 0u; i < arr->size; i++) {
        arr->data[i].number = NULL;
    }
    free(arr->data);
    free(arr);
}

//ARRAY TEST GETTERS SETTERS

TEST(ArrayTest, GetElementByIndex_First) {
    unsigned int size = 5u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    unsigned int index = 0u;
    set_element_by_index(arr, static_cast<int>(index), create((char*)"int"));
    Element* actual = get_element_by_index(arr, static_cast<int>(index));
    EXPECT_NE(actual, nullptr) << "Input: index=" << index << ", Expected: not nullptr";
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetElementByIndex_Last) {
    unsigned int size = 5u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    unsigned int index = 4u;
    set_element_by_index(arr, static_cast<int>(index), create((char*)"int"));
    Element* actual = get_element_by_index(arr, static_cast<int>(index));
    EXPECT_NE(actual, nullptr) << "Input: index=" << index << ", Expected: not nullptr";
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetElementByIndex_Middle) {
    unsigned int size = 10u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    unsigned int index = 5u;
    set_element_by_index(arr, static_cast<int>(index), create((char*)"int"));
    Element* actual = get_element_by_index(arr, static_cast<int>(index));
    EXPECT_NE(actual, nullptr) << "Input: index=" << index << ", Expected: not nullptr";
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_ValuePreserved) {
    unsigned int size = 5u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    Element* new_elem = create((char*)"int");
    int input_val = 777;
    set_int_number(new_elem, input_val);
    unsigned int index = 3u;
    set_element_by_index(arr, static_cast<int>(index), new_elem);
    Element* retrieved = get_element_by_index(arr, static_cast<int>(index));
    int expected = input_val;
    int actual = get_int_number(retrieved);
    EXPECT_EQ(actual, expected) << "Input: index=" << index << ", value=" << input_val << ", Expected: " << expected;
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_Overwrite) {
    unsigned int size = 3u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, static_cast<int>(i), create((char*)"int"));
        set_int_number(get_element_by_index(arr, static_cast<int>(i)), static_cast<int>(i) * 10);
    }
    Element* new_elem = create((char*)"int");
    int input_val = 999;
    set_int_number(new_elem, input_val);
    unsigned int index = 1u;
    set_element_by_index(arr, static_cast<int>(index), new_elem);
    int expected = input_val;
    int actual = get_int_number(get_element_by_index(arr, static_cast<int>(index)));
    EXPECT_EQ(actual, expected) << "Input: index=" << index << ", value=" << input_val << ", Expected: " << expected;
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_NegativeIndex) {
    unsigned int size = 5u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    Element* new_elem = create((char*)"int");
    int index = -1;
    int expected = 0;
    int actual = set_element_by_index(arr, index, new_elem);
    EXPECT_EQ(actual, expected) << "Input: index=" << index << ", Expected: " << expected;
    destroy_elem(new_elem);
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, SetElementByIndex_NullArray) {
    Element* new_elem = create((char*)"int");
    int index = 0;
    int expected = 0;
    int actual = set_element_by_index(nullptr, index, new_elem);
    EXPECT_EQ(actual, expected) << "Input: nullptr array, Expected: " << expected;
    destroy_elem(new_elem);
}

TEST(ArrayTest, SetElementByIndex_NullElem) {
    unsigned int size = 5u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) arr->data[i].number = NULL;
    unsigned int index = 0u;
    int expected = 0;
    int actual = set_element_by_index(arr, static_cast<int>(index), nullptr);
    EXPECT_EQ(actual, expected) << "Input: nullptr elem, Expected: " << expected;
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

//ARRAY TEST TYPE CHECK

TEST(ArrayTest, GetArrayType_Empty) {
    unsigned int input = 0u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    EXPECT_EQ(get_array_type(arr), nullptr) << "Input: size=" << input << ", Expected: nullptr";
    if (arr->data) free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetArrayType_Float) {
    unsigned int size = 3u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, static_cast<int>(i), create((char*)"float"));
    }
    const TypeElement* expected = &FloatType;
    const TypeElement* actual = get_array_type(arr);
    EXPECT_EQ(actual, expected) << "Input: array of float, Expected: &FloatType";
    for (unsigned int i = 0u; i < arr->size; i++) {
        if (arr->data[i].number) free(arr->data[i].number);
    }
    free(arr->data);
    free(arr);
}

TEST(ArrayTest, GetArrayType_NullArray) {
    EXPECT_EQ(get_array_type(nullptr), nullptr) << "Input: nullptr, Expected: nullptr";
}

//ARRAY TEST DESTROY

TEST(ArrayTest, DestroyArray_Null) {
    int expected = 0;
    int actual = destroy_array(nullptr);
    EXPECT_EQ(actual, expected) << "Input: nullptr, Expected: " << expected;
}

TEST(ArrayTest, DestroyArray_Empty) {
    unsigned int input = 0u;
    Array* arr = create_array_size_element(static_cast<int>(input));
    int expected = 1;
    int actual = destroy_array(arr);
    EXPECT_EQ(actual, expected) << "Input: empty array, Expected: " << expected;
}

TEST(ArrayTest, DestroyArray_WithIntElements) {
    unsigned int size = 3u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, static_cast<int>(i), create((char*)"int"));
    }
    int expected = 1;
    int actual = destroy_array(arr);
    EXPECT_EQ(actual, expected) << "Input: array with int, Expected: " << expected;
}

TEST(ArrayTest, DestroyArray_WithFloatElements) {
    unsigned int size = 3u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < arr->size; i++) {
        arr->data[i].number = NULL;
        set_element_by_index(arr, static_cast<int>(i), create((char*)"float"));
    }
    int expected = 1;
    int actual = destroy_array(arr);
    EXPECT_EQ(actual, expected) << "Input: array with float, Expected: " << expected;
}

//MATRIX TESTS CREATE

TEST(MatrixTest, CreateMatrix_1x1) {
    int rows = 1, cols = 1;
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_NE(actual, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(actual), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(actual), cols) << "Expected cols: " << cols;
    destroy_matrix(actual);
}

TEST(MatrixTest, CreateMatrix_1xN) {
    int rows = 1, cols = 5;
    Array* arr = create_array_size_element(5);
    for (int i = 0; i < 5; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_NE(actual, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(actual), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(actual), cols) << "Expected cols: " << cols;
    destroy_matrix(actual);
}

TEST(MatrixTest, CreateMatrix_Nx1) {
    int rows = 5, cols = 1;
    Array* arr = create_array_size_element(5);
    for (int i = 0; i < 5; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_NE(actual, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(actual), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(actual), cols) << "Expected cols: " << cols;
    destroy_matrix(actual);
}

TEST(MatrixTest, CreateMatrix_Large) {
    int rows = 10, cols = 10;
    Array* arr = create_array_size_element(100);
    for (int i = 0; i < 100; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_NE(actual, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(actual), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(actual), cols) << "Expected cols: " << cols;
    destroy_matrix(actual);
}

TEST(MatrixTest, CreateMatrix_NullArray) {
    Matrix* actual = create_matrix(nullptr, 3, 3);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr array, Expected: nullptr";
}

TEST(MatrixTest, CreateMatrix_ZeroRows) {
    int rows = 0, cols = 3;
    Array* arr = create_array_size_element(0);
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_EQ(actual, nullptr) << "Input: rows=" << rows << ", Expected: nullptr";
    if (arr) { if (arr->data) free(arr->data); free(arr); }
}

TEST(MatrixTest, CreateMatrix_ZeroCols) {
    int rows = 3, cols = 0;
    Array* arr = create_array_size_element(0);
    Matrix* actual = create_matrix(arr, rows, cols);
    EXPECT_EQ(actual, nullptr) << "Input: cols=" << cols << ", Expected: nullptr";
    if (arr) { if (arr->data) free(arr->data); free(arr); }
}

//MATRIX TESTS GETTERS

TEST(MatrixTest, GetRowsCols_1x1) {
    int rows = 1, cols = 1;
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, rows, cols);
    EXPECT_EQ(get_rows(m), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(m), cols) << "Expected cols: " << cols;
    destroy_matrix(m);
}

TEST(MatrixTest, GetRowsCols_5x7) {
    int rows = 5, cols = 7;
    Array* arr = create_array_size_element(35);
    for (int i = 0; i < 35; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, rows, cols);
    EXPECT_EQ(get_rows(m), rows) << "Expected rows: " << rows;
    EXPECT_EQ(get_cols(m), cols) << "Expected cols: " << cols;
    destroy_matrix(m);
}

TEST(MatrixTest, GetRowsCols_NullMatrix) {
    EXPECT_EQ(get_rows(nullptr), 0) << "Input: nullptr, Expected: 0";
    EXPECT_EQ(get_cols(nullptr), 0) << "Input: nullptr, Expected: 0";
}

TEST(MatrixTest, GetArray_ReturnsValid) {
    unsigned int size = 4u;
    Array* arr = create_array_size_element(static_cast<int>(size));
    for (unsigned int i = 0u; i < size; i++) set_element_by_index(arr, static_cast<int>(i), create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 2, 2);
    EXPECT_NE(get_array(m), nullptr) << "Expected: not nullptr";
    EXPECT_EQ(get_array(m)->size, size) << "Expected size: " << size;
    destroy_matrix(m);
}

TEST(MatrixTest, GetArray_NullMatrix) {
    EXPECT_EQ(get_array(nullptr), nullptr) << "Input: nullptr, Expected: nullptr";
}

//MATRIX TESTS PRINT

TEST(MatrixTest, PrintMatrix_1x1) {
    int val = 42;
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(arr, 0), val);
    Matrix* m = create_matrix(arr, 1, 1);
    char* str = print_matrix(m);
    EXPECT_NE(str, nullptr) << "Input: value=" << val << ", Expected: not nullptr";
    bool found = strstr(str, "42") != nullptr;
    EXPECT_TRUE(found) << "Input: value=" << val << ", Expected substring: 42";
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
    EXPECT_NE(str, nullptr) << "Expected: not nullptr";
    bool found = strstr(str, "│") != nullptr;
    EXPECT_TRUE(found) << "Expected substring: │";
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
    EXPECT_NE(str, nullptr) << "Expected: not nullptr";
    free(str);
    destroy_matrix(m);
}

TEST(MatrixTest, PrintMatrix_NullMatrix) {
    char* actual = print_matrix(nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr, Expected: nullptr";
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

//MATRIX TESTS SUM

TEST(MatrixTest, SumMatrix_1x1) {
    int val_a = 5, val_b = 3;
    int expected = 8;
    Array* a1 = create_array_size_element(1);
    Array* a2 = create_array_size_element(1);
    set_element_by_index(a1, 0, create_null((char*)"int"));
    set_element_by_index(a2, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(a1, 0), val_a);
    set_int_number(get_element_by_index(a2, 0), val_b);
    Matrix* m1 = create_matrix(a1, 1, 1);
    Matrix* m2 = create_matrix(a2, 1, 1);
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_NE(res, nullptr) << "Input: " << val_a << " + " << val_b << ", Expected: not nullptr";
    int actual = get_int_number(get_element_by_index(get_array(res), 0));
    EXPECT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(res);
}

TEST(MatrixTest, SumMatrix_Float) {
    float val_a = 1.5f, val_b = 2.5f;
    float expected = 4.0f;
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(a1, i, create_null((char*)"float"));
        set_element_by_index(a2, i, create_null((char*)"float"));
        set_float_number(get_element_by_index(a1, i), val_a);
        set_float_number(get_element_by_index(a2, i), val_b);
    }
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* res = sum_matrix(m1, m2);
    EXPECT_NE(res, nullptr) << "Input: " << val_a << " + " << val_b << ", Expected: not nullptr";
    float actual = get_float_number(get_element_by_index(get_array(res), 0));
    EXPECT_FLOAT_EQ(actual, expected) << "Input: " << val_a << " + " << val_b << ", Expected: " << expected;
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
    Matrix* actual = sum_matrix(m1, m2);
    EXPECT_EQ(actual, nullptr) << "Input: int + float, Expected: nullptr";
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(MatrixTest, SumMatrix_NullFirst) {
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a2, i, create_null((char*)"int"));
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* actual = sum_matrix(nullptr, m2);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr + m2, Expected: nullptr";
    destroy_matrix(m2);
}

TEST(MatrixTest, SumMatrix_NullSecond) {
    Array* a1 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* actual = sum_matrix(m1, nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: m1 + nullptr, Expected: nullptr";
    destroy_matrix(m1);
}

//MATRIX TESTS MULTIPLY

TEST(MatrixTest, MultMatrix_2x2_2x2) {
    int val_a = 1, val_b = 2;
    Array* a1 = create_array_size_element(4);
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(a1, i, create_null((char*)"int"));
        set_element_by_index(a2, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(a1, i), val_a);
        set_int_number(get_element_by_index(a2, i), val_b);
    }
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* actual = mult_matrix(m1, m2);
    EXPECT_NE(actual, nullptr) << "Input: " << val_a << " * " << val_b << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(actual), 2) << "Expected rows: 2";
    EXPECT_EQ(get_cols(actual), 2) << "Expected cols: 2";
    destroy_matrix(m1);
    destroy_matrix(m2);
    destroy_matrix(actual);
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
    Matrix* actual = mult_matrix(m1, m2);
    EXPECT_EQ(actual, nullptr) << "Input: 2x3 * 2x3, Expected: nullptr";
    destroy_matrix(m1);
    destroy_matrix(m2);
}

TEST(MatrixTest, MultMatrix_NullFirst) {
    Array* a2 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a2, i, create_null((char*)"int"));
    Matrix* m2 = create_matrix(a2, 2, 2);
    Matrix* actual = mult_matrix(nullptr, m2);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr * m2, Expected: nullptr";
    destroy_matrix(m2);
}

TEST(MatrixTest, MultMatrix_NullSecond) {
    Array* a1 = create_array_size_element(4);
    for (int i = 0; i < 4; i++) set_element_by_index(a1, i, create_null((char*)"int"));
    Matrix* m1 = create_matrix(a1, 2, 2);
    Matrix* actual = mult_matrix(m1, nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: m1 * nullptr, Expected: nullptr";
    destroy_matrix(m1);
}

//MATRIX TESTS TRANSPOSE

TEST(MatrixTest, TransposeMatrix_1x1) {
    int val = 42;
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    set_int_number(get_element_by_index(arr, 0), val);
    Matrix* m = create_matrix(arr, 1, 1);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr) << "Input: " << val << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(t), 1) << "Expected rows: 1";
    EXPECT_EQ(get_cols(t), 1) << "Expected cols: 1";
    int actual = get_int_number(get_element_by_index(get_array(t), 0));
    EXPECT_EQ(actual, val) << "Expected: " << val;
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_1xN) {
    int rows = 1, cols = 4;
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, rows, cols);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(t), cols) << "Expected rows: " << cols;
    EXPECT_EQ(get_cols(t), rows) << "Expected cols: " << rows;
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Nx1) {
    int rows = 4, cols = 1;
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, rows, cols);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr) << "Input: " << rows << "x" << cols << ", Expected: not nullptr";
    EXPECT_EQ(get_rows(t), cols) << "Expected rows: " << cols;
    EXPECT_EQ(get_cols(t), rows) << "Expected cols: " << rows;
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Float) {
    int rows = 2, cols = 3;
    Array* arr = create_array_size_element(6);
    for (int i = 0; i < 6; i++) {
        set_element_by_index(arr, i, create_null((char*)"float"));
        set_float_number(get_element_by_index(arr, i), (i + 1) * 0.5f);
    }
    Matrix* m = create_matrix(arr, rows, cols);
    Matrix* t = transponate_matrix(m);
    EXPECT_NE(t, nullptr) << "Input: " << rows << "x" << cols << " float, Expected: not nullptr";
    EXPECT_EQ(get_rows(t), cols) << "Expected rows: " << cols;
    EXPECT_EQ(get_cols(t), rows) << "Expected cols: " << rows;
    destroy_matrix(m);
    destroy_matrix(t);
}

TEST(MatrixTest, TransposeMatrix_Null) {
    Matrix* actual = transponate_matrix(nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr, Expected: nullptr";
}

//MATRIX TESTS STRING PARSING

TEST(MatrixTest, StringToMatrix_1x1_Int) {
    char input[] = "1 1 1\n42";
    int exp_rows = 1, exp_cols = 1, exp_val = 42;
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr) << "Input: \"" << input << "\", Expected: not nullptr";
    EXPECT_EQ(get_rows(m), exp_rows) << "Input: \"" << input << "\", Expected rows: " << exp_rows;
    EXPECT_EQ(get_cols(m), exp_cols) << "Input: \"" << input << "\", Expected cols: " << exp_cols;
    int actual = get_int_number(get_element_by_index(get_array(m), 0));
    EXPECT_EQ(actual, exp_val) << "Input: \"" << input << "\", Expected: " << exp_val;
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_3x3_Int) {
    char input[] = "3 3 1\n1 2 3 4 5 6 7 8 9";
    int exp_rows = 3, exp_cols = 3;
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr) << "Input: \"" << input << "\", Expected: not nullptr";
    EXPECT_EQ(get_rows(m), exp_rows) << "Input: \"" << input << "\", Expected rows: " << exp_rows;
    EXPECT_EQ(get_cols(m), exp_cols) << "Input: \"" << input << "\", Expected cols: " << exp_cols;
    for (int i = 0; i < 9; i++) {
        int expected = i + 1;
        int actual = get_int_number(get_element_by_index(get_array(m), i));
        EXPECT_EQ(actual, expected) << "Input: \"" << input << "\", index=" << i << ", Expected: " << expected;
    }
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_2x2_Float) {
    char input[] = "2 2 2\n1.1 2.2 3.3 4.4";
    float exp_val_0 = 1.1f, exp_val_3 = 4.4f;
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr) << "Input: \"" << input << "\", Expected: not nullptr";
    float actual_0 = get_float_number(get_element_by_index(get_array(m), 0));
    EXPECT_FLOAT_EQ(actual_0, exp_val_0) << "Input: \"" << input << "\", index=0, Expected: " << exp_val_0;
    float actual_3 = get_float_number(get_element_by_index(get_array(m), 3));
    EXPECT_FLOAT_EQ(actual_3, exp_val_3) << "Input: \"" << input << "\", index=3, Expected: " << exp_val_3;
    destroy_matrix(m);
}

TEST(MatrixTest, StringToMatrix_InvalidHeader) {
    char input[] = "abc 2 1\n1 2";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_ZeroRows) {
    char input[] = "0 2 1\n";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_ZeroCols) {
    char input[] = "2 0 1\n1 2";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_InvalidType) {
    char input[] = "2 2 3\n1 2 3 4";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_NotEnoughValues) {
    char input[] = "2 2 1\n1 2 3";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_NullInput) {
    Matrix* actual = string_to_matrix(nullptr);
    EXPECT_EQ(actual, nullptr) << "Input: nullptr, Expected: nullptr";
}

TEST(MatrixTest, StringToMatrix_EmptyInput) {
    char input[] = "";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

//MATRIX TESTS DESTROY

TEST(MatrixTest, DestroyMatrix_Null) {
    int expected = 0;
    int actual = destroy_matrix(nullptr);
    EXPECT_EQ(actual, expected) << "Input: nullptr, Expected: " << expected;
}

TEST(MatrixTest, DestroyMatrix_1x1) {
    Array* arr = create_array_size_element(1);
    set_element_by_index(arr, 0, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 1, 1);
    int expected = 1;
    int actual = destroy_matrix(m);
    EXPECT_EQ(actual, expected) << "Input: 1x1 matrix, Expected: " << expected;
}

TEST(MatrixTest, DestroyMatrix_Large) {
    Array* arr = create_array_size_element(100);
    for (int i = 0; i < 100; i++) set_element_by_index(arr, i, create_null((char*)"int"));
    Matrix* m = create_matrix(arr, 10, 10);
    int expected = 1;
    int actual = destroy_matrix(m);
    EXPECT_EQ(actual, expected) << "Input: 10x10 matrix, Expected: " << expected;
}

TEST(MatrixTest, DestroyMatrix_MultipleNoLeak) {
    for (int i = 0; i < 10; i++) {
        Array* arr = create_array_size_element(4);
        for (int j = 0; j < 4; j++) set_element_by_index(arr, j, create_null((char*)"int"));
        Matrix* m = create_matrix(arr, 2, 2);
        if (m) destroy_matrix(m);
    }
}

//HELPER FUNCTION TESTS

TEST(HelperTest, Max_Equal) {
    int a = 5, b = 5;
    int expected = 5;
    int actual = global_max(a, b);
    EXPECT_EQ(actual, expected) << "Input: " << a << ", " << b << ", Expected: " << expected;
}

TEST(HelperTest, Max_Negative) {
    int a1 = -5, b1 = -3;
    int exp1 = -3;
    EXPECT_EQ(global_max(a1, b1), exp1) << "Input: " << a1 << ", " << b1 << ", Expected: " << exp1;
    int a2 = -10, b2 = -1;
    int exp2 = -1;
    EXPECT_EQ(global_max(a2, b2), exp2) << "Input: " << a2 << ", " << b2 << ", Expected: " << exp2;
}

TEST(HelperTest, Max_Large) {
    int a = 1000000, b = 999999;
    int expected = 1000000;
    EXPECT_EQ(global_max(a, b), expected) << "Input: " << a << ", " << b << ", Expected: " << expected;
}

TEST(HelperTest, Min_Equal) {
    int a = 5, b = 5;
    int expected = 5;
    EXPECT_EQ(global_min(a, b), expected) << "Input: " << a << ", " << b << ", Expected: " << expected;
}

TEST(HelperTest, Min_Negative) {
    int a1 = -5, b1 = -3;
    int exp1 = -5;
    EXPECT_EQ(global_min(a1, b1), exp1) << "Input: " << a1 << ", " << b1 << ", Expected: " << exp1;
    int a2 = -10, b2 = -1;
    int exp2 = -10;
    EXPECT_EQ(global_min(a2, b2), exp2) << "Input: " << a2 << ", " << b2 << ", Expected: " << exp2;
}

TEST(HelperTest, Min_Large) {
    int a = 1000000, b = 999999;
    int expected = 999999;
    EXPECT_EQ(global_min(a, b), expected) << "Input: " << a << ", " << b << ", Expected: " << expected;
}

TEST(HelperTest, FormatMatrix_Basic) {
    char data[] = "1 2 3 4 5 6";
    char* result = format_matrix(2, 3, &IntType, data);
    EXPECT_NE(result, nullptr) << "Input: 2 3 int \"1 2 3 4 5 6\", Expected: not nullptr";
    bool found1 = strstr(result, "2 3 1") != nullptr;
    EXPECT_TRUE(found1) << "Expected substring: 2 3 1";
    bool found2 = strstr(result, "1 2 3 4 5 6") != nullptr;
    EXPECT_TRUE(found2) << "Expected substring: 1 2 3 4 5 6";
    free((void*)result);
}

TEST(HelperTest, FormatMatrix_NullData) {
    char* result = format_matrix(1, 1, &IntType, nullptr);
    EXPECT_EQ(result, nullptr) << "Input: nullptr data, Expected: nullptr";
}

TEST(HelperTest, FormatMatrix_ZeroSize) {
    char data[] = "";
    char* result = format_matrix(0, 0, &IntType, data);
    EXPECT_NE(result, nullptr) << "Input: 0 0 \"\", Expected: not nullptr";
    free((void*)result);
}

TEST(HelperTest, ClearBuffer_Exists) {
    EXPECT_TRUE(clear_buffer != nullptr) << "Expected: not nullptr";
}

//INTEGRATION TESTS

TEST(IntegrationTest, CreatePrintDestroy) {
    Array* arr = create_array_size_element(4);
    for (int i = 0; i < 4; i++) {
        set_element_by_index(arr, i, create_null((char*)"int"));
        set_int_number(get_element_by_index(arr, i), i + 1);
    }
    Matrix* m = create_matrix(arr, 2, 2);
    char* str = print_matrix(m);
    EXPECT_NE(str, nullptr) << "Expected: not nullptr";
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
    EXPECT_NE(res, nullptr) << "Expected: not nullptr";
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
    char input1[] = "2 2 1\n1 2 3 4";
    char input2[] = "2 2 1\n5 6 7 8";
    Matrix* m1 = string_to_matrix(input1);
    Matrix* m2 = string_to_matrix(input2);
    if (m1 && m2) {
        Matrix* res = sum_matrix(m1, m2);
        if (res) {
            int expected = 6;
            int actual = get_int_number(get_element_by_index(get_array(res), 0));
            EXPECT_EQ(actual, expected) << "Input: " << input1 << " + " << input2 << ", Expected: " << expected;
            destroy_matrix(res);
        }
    }
    if (m1) destroy_matrix(m1);
    if (m2) destroy_matrix(m2);
}

//EDGE CASE TESTS

TEST(EdgeCaseTest, Element_OperationsWithZero) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, 0);
    set_int_number(b, 0);
    Element* sum = sum_int(a, b);
    int exp_sum = 0;
    int act_sum = get_int_number(sum);
    EXPECT_EQ(act_sum, exp_sum) << "Input: 0 + 0, Expected sum: " << exp_sum;
    Element* prod = mult_int(a, b);
    int exp_prod = 0;
    int act_prod = get_int_number(prod);
    EXPECT_EQ(act_prod, exp_prod) << "Input: 0 * 0, Expected prod: " << exp_prod;
    destroy_elem(a); destroy_elem(b); destroy_elem(sum); destroy_elem(prod);
}

TEST(EdgeCaseTest, Element_OperationsWithMaxValues) {
    Element* a = create((char*)"int");
    Element* b = create((char*)"int");
    set_int_number(a, INT_MAX / 2);
    set_int_number(b, INT_MAX / 2);
    Element* sum = sum_int(a, b);
    EXPECT_NE(sum, nullptr) << "Input: INT_MAX/2 + INT_MAX/2, Expected: not nullptr";
    destroy_elem(a); destroy_elem(b);
    if (sum) destroy_elem(sum);
}

TEST(EdgeCaseTest, Matrix_EmptyStringParse) {
    char input[] = "";
    Matrix* actual = string_to_matrix(input);
    EXPECT_EQ(actual, nullptr) << "Input: \"" << input << "\", Expected: nullptr";
}

TEST(EdgeCaseTest, Matrix_WhitespaceInString) {
    char input[] = "  2  2  1  \n  1  2  3  4  ";
    Matrix* actual = string_to_matrix(input);
    EXPECT_NE(actual, nullptr) << "Input: \"" << input << "\", Expected: not nullptr";
    if (actual) destroy_matrix(actual);
}

TEST(EdgeCaseTest, Matrix_NegativeValues) {
    char input[] = "2 2 1\n-1 -2 -3 -4";
    int expected = -1;
    Matrix* m = string_to_matrix(input);
    EXPECT_NE(m, nullptr) << "Input: \"" << input << "\", Expected: not nullptr";
    int actual = get_int_number(get_element_by_index(get_array(m), 0));
    EXPECT_EQ(actual, expected) << "Input: \"" << input << "\", Expected: " << expected;
    if (m) destroy_matrix(m);
}

//main

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
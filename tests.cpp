#include <gtest/gtest.h>
#include "func.h"

// Объявляем, что используем C-функции
extern "C" {
    #include "func.h"
}

// Тест умножения целых чисел
TEST(MultIntTest, MultiplyPositiveNumbers) {
    // Создаем тестовые элементы
    Element a = create_int_elem();
    Element b = create_int_elem();
    
    // Устанавливаем значения
    int val_a = 5;
    int val_b = 3;
    a.number = malloc(sizeof(int));
    b.number = malloc(sizeof(int));
    *(int*)a.number = val_a;
    *(int*)b.number = val_b;
    a.size = sizeof(int);
    b.size = sizeof(int);
    
    // Вызываем функцию умножения
    Element result = mult_int(&a, &b);
    
    // Проверяем результат
    EXPECT_EQ(*(int*)result.number, 15);
    
    // Очищаем память
    if (a.number) free(a.number);
    if (b.number) free(b.number);
    if (result.number) free(result.number);
}

TEST(MultIntTest, MultiplyWithZero) {
    Element a = create_int_elem();
    Element b = create_int_elem();
    
    int val_a = 10;
    int val_b = 0;
    a.number = malloc(sizeof(int));
    b.number = malloc(sizeof(int));
    *(int*)a.number = val_a;
    *(int*)b.number = val_b;
    a.size = sizeof(int);
    b.size = sizeof(int);
    
    Element result = mult_int(&a, &b);
    
    EXPECT_EQ(*(int*)result.number, 0);
    
    if (a.number) free(a.number);
    if (b.number) free(b.number);
    if (result.number) free(result.number);
}

TEST(MultIntTest, MultiplyNegativeNumbers) {
    Element a = create_int_elem();
    Element b = create_int_elem();
    
    int val_a = -4;
    int val_b = 7;
    a.number = malloc(sizeof(int));
    b.number = malloc(sizeof(int));
    *(int*)a.number = val_a;
    *(int*)b.number = val_b;
    a.size = sizeof(int);
    b.size = sizeof(int);
    
    Element result = mult_int(&a, &b);
    
    EXPECT_EQ(*(int*)result.number, -28); 
    
    if (a.number) free(a.number);
    if (b.number) free(b.number);
    if (result.number) free(result.number);
}
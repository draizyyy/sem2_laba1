# === Компиляторы (MinGW) ===
CC = gcc
CXX = g++

# === Флаги ===
CFLAGS = -Wall -Wextra -g -I.
CXXFLAGS = -Wall -Wextra -g -std=c++17 -I.

# === Пути к Google Test ===
GTEST_INC = -IC:/libs/googletest/install/include
GTEST_LIB = -LC:/libs/googletest/install/lib -lgtest -lgtest_main

# === Основная программа ===
TARGET = main.exe
SRCS = main.c func.c array.c element.c matrix.c
OBJS = main.o func.o array.o element.o matrix.o

# === Тесты ===
TEST_DIR = build_test
TEST_EXE = $(TEST_DIR)/run_tests.exe
TEST_SRC = tests/test_func.cpp
TEST_OBJS = $(TEST_DIR)/test_func.o $(TEST_DIR)/func.o $(TEST_DIR)/array.o $(TEST_DIR)/element.o $(TEST_DIR)/matrix.o

# === Цели ===
.PHONY: all main test clean rebuild help

all: help

help:
	@echo "=== Команды ==="
	@echo "  make main   - собрать main.exe"
	@echo "  make test   - собрать и запустить тесты"
	@echo "  make clean  - очистить всё"
	@echo "  make rebuild - полная пересборка"

# === ОСНОВНАЯ ПРОГРАММА ===
main: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c func.h array.h element.h matrix.h
	$(CC) $(CFLAGS) -c main.c -o main.o

func.o: func.c func.h element.h matrix.h
	$(CC) $(CFLAGS) -c func.c -o func.o

array.o: array.c array.h func.h element.h matrix.h
	$(CC) $(CFLAGS) -c array.c -o array.o

element.o: element.c element.h
	$(CC) $(CFLAGS) -c element.c -o element.o

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o

# === ТЕСТЫ ===
test: $(TEST_EXE)
	@echo "=== Запуск тестов ==="
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_SRC) func.c array.c element.c matrix.c func.h array.h element.h matrix.h
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -c $(TEST_SRC) -o $(TEST_DIR)/test_func.o
	$(CC) $(CFLAGS) -c func.c -o $(TEST_DIR)/func.o
	$(CC) $(CFLAGS) -c array.c -o $(TEST_DIR)/array.o
	$(CC) $(CFLAGS) -c element.c -o $(TEST_DIR)/element.o
	$(CC) $(CFLAGS) -c matrix.c -o $(TEST_DIR)/matrix.o
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -o $@ $(TEST_OBJS) $(GTEST_LIB)

# === ОЧИСТКА ===
clean:
	@echo "=== Очистка ==="
	rm -f *.o *.exe
	rm -rf $(TEST_DIR)
	@echo "Готово!"

rebuild: clean all
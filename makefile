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
SRCS = main.c func.c massive.c
OBJS = main.o func.o massive.o

# === Тесты ===
TEST_DIR = build_test
TEST_EXE = $(TEST_DIR)/run_tests.exe
TEST_SRC = tests/test_func.cpp

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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

<<<<<<< HEAD
# === ТЕСТЫ ===
test: $(TEST_EXE)
	@echo "=== Запуск тестов ==="
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_SRC) func.c massive.c func.h massive.h
	mkdir -p $(TEST_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -c $(TEST_SRC) -o $(TEST_DIR)/test_func.o
	$(CC) $(CFLAGS) -c func.c -o $(TEST_DIR)/func.o
	$(CC) $(CFLAGS) -c massive.c -o $(TEST_DIR)/massive.o
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -o $@ $(TEST_DIR)/test_func.o $(TEST_DIR)/func.o $(TEST_DIR)/massive.o $(GTEST_LIB)

# === ОЧИСТКА ===
clean:
	@echo "=== Очистка ==="
	rm -f *.o *.exe
	rm -rf $(TEST_DIR)
	@echo "Готово!"

rebuild: clean main
=======
main.o: main.c func.h massive.h
func.o: func.c func.h
massive.o: massive.c massive.h

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
>>>>>>> 8dd5ba627c65a306108ea5a79fd4f8204b2dea7d

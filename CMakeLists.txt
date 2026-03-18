cmake_minimum_required(VERSION 3.15)
project(TestRunner C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Библиотека (БЕЗ main.c!)
add_library(mylib func.c massive.c)
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Пути к Google Test
set(GTEST_INCLUDE_DIR "C:/libs/googletest/install/include")
set(GTEST_LIB_DIR "C:/libs/googletest/install/lib")

# Тесты
add_executable(run_tests tests/test_func.cpp)
target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIR})
target_link_libraries(run_tests PRIVATE 
    mylib 
    ${GTEST_LIB_DIR}/libgtest.a 
    ${GTEST_LIB_DIR}/libgtest_main.a
)

enable_testing()
add_test(NAME MyTests COMMAND run_tests)
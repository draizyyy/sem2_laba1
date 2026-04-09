cmake_minimum_required(VERSION 3.15)
project(TestRunner C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(matrix_lib func.c massive.c)
target_include_directories(matrix_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(GTEST_INCLUDE_DIR "C:/libs/googletest/install/include")
set(GTEST_LIB_DIR "C:/libs/googletest/install/lib")


add_executable(run_tests tests/test_func.cpp)
target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIR})
target_link_libraries(run_tests PRIVATE 
    matrix_lib 
    ${GTEST_LIB_DIR}/libgtest.a 
    ${GTEST_LIB_DIR}/libgtest_main.a
)

enable_testing()
add_test(NAME MatrixTests COMMAND run_tests)
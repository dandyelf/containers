//
// Created by Left Ranae on 15.04.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "../s21_stack.h"

namespace s21vector {
namespace  tests {
namespace {

// The fixture for testing class Foo.
class s21StackTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST(StackTests, StandartConstructor)
{
  Stack <int> myStack(5);
 
    // заполняем стек
    std::cout << "Заталкиваем элементы в стек: ";
    int ct = 0;
    int temp = 4354;
    while (ct++ != 5)
    {
        temp *= ct;
        myStack.push(temp);
    }
 
    myStack.printStack(); // вывод стека на экран
 
    std::cout << "\nУдаляем два элемента из стека:\n";
 
    myStack.pop(); // удаляем элемент из стека
    myStack.pop(); // удаляем элемент из стека
    myStack.printStack(); // вывод стека на экран
}

TEST(StackTests, ParamConstructor)
{
  
}

TEST(StackTests, InitializerListConstructor)
{
 
}

}  // namespace
}  // namespace vector
}  // namespace testsmake

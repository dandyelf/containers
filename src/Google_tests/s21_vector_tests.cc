//
// Created by Left Ranae on 15.04.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "../s21_vector.h"
#include <string>-

namespace s21vector {
namespace  tests {
namespace {

// The fixture for testing class Foo.
class s21VectorTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST(VectorTests, StandartConstructor)
{
  s21::Vector<std::string>   as;
  s21::Vector<int> v(2);
  v.Reserve(10);
  v.At(1) = 1;
}

TEST(VectorTests, ParamConstructor)
{
  s21::Vector<std::string> v(3);
  s21::Vector<std::string> v1(300000);
  s21::Vector<std::string> v2(0);
  // EXPECT_ANY_THROW(s21::Vector<std::string> v3(300000000000));
}

TEST(VectorTests, InitializerListConstructor)
{
  // s21::Vector<std::string> v = {"AAAA", "BBBBB"};
  std::vector<std::string> v1 = {"AAAA", "BBBBB"};
  std::cout << v1.at(0) ;
}

}  // namespace
}  // namespace vector
}  // namespace testsmake

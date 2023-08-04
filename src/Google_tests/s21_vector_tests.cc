//
// Created by Left Ranae on 15.04.2023.
//
#include <iostream>
#include "gtest/gtest.h"
#include "../s21_vector.cc"
#include <string>
#include <vector>

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
  s21::Vector<std::string> v1 = {"AAAA", "BBBBB"};
  std::vector<std::string> jo = {"AAAAAAA", "BBBBBB", "CCCCCCC"};
  std::string s1("BUUU");
  std::string s2("BAAA");
  s21::Vector <std::string> va = {s1, s2};
  std::cout << *jo.begin() << std::endl;
}

TEST(VectorTests, PushBack)
{
  s21::Vector<std::string> v1(6);
  std::string str("CCCCCCCCC");
  v1.Reserve(3);
  v1.Push_back(str);
  // std::cout << v1.Size();

  // std::cout << v1.At(0);
}

TEST(VectorTests, BeginEnd)
{
  s21::Vector<std::string> ju (6);
  
}

}  // namespace
}  // namespace vector
}  // namespace testsmake

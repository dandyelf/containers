//
// Created by Left Ranae on 15.04.2023.
//
#include <iostream>
#include <string>
#include <vector>

#include "../s21_vector.cc"
#include "gtest/gtest.h"

namespace s21vector {
namespace tests {
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
TEST(VectorTests, StandartConstructor) {
  s21::Vector<std::string> v;
  s21::Vector<int> v1;
}

TEST(VectorTests, ParamConstructor) {
  s21::Vector<std::string> v(3);
  s21::Vector<std::string> v1(300000);
  s21::Vector<std::string> v2(0);
  // EXPECT_ANY_THROW(s21::Vector<std::string> v3(300000000000000));
}

TEST(VectorTests, InitializerListConstructor) {
  s21::Vector<std::string> v1 = {"111", "222"};
  std::string s1("111");
  std::string s2("222");
  s21::Vector<std::string> v2 = {s1, s2};
}

TEST(VectorTests, PushBack) {
  s21::Vector<std::string> v1(7);
  std::string str("111");
  v1.Push_back(str);
  v1.Push_back(str);
  v1.Push_back(str);
  v1.Push_back(str);
}

TEST(VectorTests, Reserve) {
  s21::Vector<std::string> v1(6);
  std::string str("111");
  v1.Push_back(str);
  v1.Reserve(13);
  v1.Reserve(40);
  v1.Reserve(50);
  v1.Reserve(60);
  v1.Reserve(70);
  ASSERT_EQ("111", v1.At(6));
  ASSERT_EQ("", v1.At(1));
}

TEST(VectorTests, BeginEnd) {
  s21::Vector<std::string> ju(6);
  ju.At(0) = "111";
  ju.At(1) = "222";
  ju.At(2) = "333";
  s21::Vector<std::string>::iterator ite = ju.begin();
  std::cout << *ite << std::endl;
  int i = 0;
  for (auto it = ju.begin(); it != ju.end(); it++) {
    std::cout << *it << std::endl;
    i++;
  }
}

TEST(VectorTests, ConstBeginEnd) {
  s21::Vector<std::string> ju(3);
  ju.At(0) = "111";
  ju.At(1) = "111";
  ju.At(2) = "111";
  const s21::Vector<std::string>::iterator ite = ju.begin();
  ASSERT_EQ("111", *ite);
  int i = 0;
  for (auto it = ju.begin(); it != ju.end(); it++) {
    ASSERT_EQ("111", *it);
    i++;
  }
}

TEST(VectorTests, StdVector) {
  std::vector<std::string> v1 = {"111", "222"};
  std::string s1("111");
  std::string s2("222");
  std::vector<std::string> v2 = {s1, s2};
}

}  // namespace
}  // namespace tests
}  // namespace s21vector

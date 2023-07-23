//
// Created by Left Ranae on 15.04.2023.
//

#include <iostream>

#include "gtest/gtest.h"
#include "../s21_vector.h"
#include <string>

namespace vector {
namespace  tests {
namespace {

// The fixture for testing class Foo.
class VectorTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST(VectorTests, StandartConstructor)
{
  s21::Vector<int> v;
  // v.Resise(10);
}

TEST(VectorTests, ParamConstructor)
{
  s21::Vector<std::string> v(3);
  s21::Vector<std::string> v1(3000000);
  s21::Vector<std::string> v2(0);
  EXPECT_ANY_THROW(s21::Vector<std::string> v3(300000000000));
}

}  // namespace
}  // namespace vector
}  // namespace tests

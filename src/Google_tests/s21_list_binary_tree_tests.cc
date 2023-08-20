//
// Created by Left Ranae on 15.04.2023.
//
#include <iostream>

#include "../s21_binary_tree.h"
#include "gtest/gtest.h"

namespace s21binaryTree {
namespace tests {
namespace {

// The fixture for testing class Foo.
class s21BinaryTreeTests : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if their bodies would
  // be empty.
  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST(binaryTreeTests, StandartConstructor) { s21::BinaryTree<int> A; }

TEST(BinaryTreeTests, Insert) { s21::BinaryTree<int> A; }

TEST(BinaryTreeTests, InitializerListConstructor) {}

}  // namespace
}  // namespace tests
}  // namespace s21binaryTree

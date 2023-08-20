//
// Created by Left Ranae on 15.04.2023.
//
#ifndef CONTAINERS_SRC_S21_LIST_H_
#define CONTAINERS_SRC_S21_LIST_H_

#include <cmath>
#include <iostream>
#include <memory>

namespace s21 {
template <typename T>
class BinaryTree {
  //   template <typename value_type>
  //   class ListIterator;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 public:
  //  private:

  class Node {
   public:
    int key_{};
    int value_{};
    Node* left_{};
    Node* right_{};
    Node(){};
    Node(int key, int value) : key_(key), value_(value) {}
    ~Node(){};
  };
  void insert(Node node, int key, int value) {
    if (key < node.key_)
      if (node.left_ == nullptr) {
        Node tmp(key, value);
        node.left_ = tmp;
      }
  }

};  // class List
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_LIST_H_
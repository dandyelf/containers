//
// Created by Left Ranae on 15.04.2023.
//

#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

#include <iostream>

namespace s21 {
class Vector {
 public:
  void PushBack();

 private:
  size_t size_{};
  size_t capaciti_{};
};  // class list
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_VECTOR_H_
//
// Created by Left Ranae on 15.04.2023.
//

#include <vector>

#include "s21_containers.h"
#include "s21_matrix_oop.h"

int main(int argc, char const* argv[]) {
  if (argc && argv) {
    // s21::Vector<S21Matrix> m(6);
    // S21Matrix A(3, 3);
    // S21Matrix B(4, 4);
    // m.At(1) = A;
    // m.At(2) = B;
    s21::Vector<std::string> v(2);
    v.At(0) = "aa";
    v.At(1) = "bb";
    std::cout << v.At(0) << std::endl;
    v.Reserve(3);
    std::cout << v.At(1) << std::endl;
  }
  return 0;
}

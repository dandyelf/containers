//
// Created by Left Ranae on 15.04.2023.
//

#include <vector>

#include "s21_containers.h"
#include "s21_matrix_oop.h"

int main(int argc, char const* argv[]) {
  if (argc && argv) {
    s21::Vector<S21Matrix> m(6);
    S21Matrix A(3, 3);
    S21Matrix B(4, 4);
    m.At(1) = A;
    m.At(2) = B;
    std::cout << "Tut" << std::endl;
    // m.Reserve(10);
    std::cout << "Tut" << std::endl;
  }
  return 0;
}

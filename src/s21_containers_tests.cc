//
// Created by Left Ranae on 15.04.2023.
//

#include <vector>

#include "s21_containers.h"
#include "s21_matrix_oop.h"

int main(int argc, char const *argv[]) {
  if (argc && argv) {
    s21::Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    for (size_t i = 0; i < v.size(); i++) {
      std::cout << v.at(i);
    }
    std::vector<int> b = {7, 8, 9};
    b.push_back(10);
    for (size_t i = 0; i < b.size(); i++) {
      std::cout << b.at(i);
    }
    s21::Vector<S21Matrix> m(6);
    std::cout << "Tut" << std::endl;
    std::vector<S21Matrix> m1(6);
  }
  return 0;
}

//
// Created by Left Ranae on 15.04.2023.
//

#include <vector>

#include "s21_containers.h"
#include "s21_matrix_oop.h"

int main(int argc, char** argv) {
  if (argc && argv) {
    size_t u{};
    s21::Vector<std::string> v(1000);
    v.At(0) = "AAAAAAAAAAAAAAAa";
    for (size_t i = 0; i < 3; i++) {
      std::cin >> u;
      if (!u) {
        u = 1500;
      }
      try {
        v.Reserve(u);
        std::cout << v.At(0) << std::endl;
      } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
      }
    }
  }
}

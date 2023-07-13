//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_containers.h"

namespace s21_test {
class word {
 public:
  int arr_length = 5;
  int arr[5];
  int SearchArr();
};  // class list
}  // namespace s21_test

int s21_test::word::SearchArr() {
  for (int i = 0; i < arr_length; i++)
    if (arr[i] != 0) std::cout << "SearchArr: not empty #" << i << std::endl;
  return 0;
}

int main(int argc, char const *argv[]) {
  if (argc && argv) {
    s21_test::word a;
    a.arr[0] = 1;
    a.arr[3] = 1;
    a.SearchArr();
    s21::Vector<int> v = {1, 2, 3, 4, 5};
    v.push_back(6);
    for (size_t i = 0; i < v.size(); i++) {
      std::cout << v.at(i);
    }
  }
  return 0;
}

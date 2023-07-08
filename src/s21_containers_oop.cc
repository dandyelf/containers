//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_containers_oop.h"

#include <iostream>

int list::SearchArr() {
  for (int i = 0; i < arr_length; i++)
    if (arr[i] != 0) std::cout << "not empty #" << i << std::endl;
  return 0;
}

int main(int argc, char const *argv[]) {
  if (argc && argv) {
    list a;
    a.arr[0] = 1;
    a.arr[3] = 1;
    a.SearchArr();
  }
  return 0;
}
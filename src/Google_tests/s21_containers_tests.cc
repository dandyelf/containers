//
// Created by Left Ranae on 15.04.2023.
//

#include <iostream>

#include "gtest/gtest.h"
#include "../s21_containers.h"

TEST(test_case_name, test_name)
{
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}








// int main(int argc, char** argv) {
//   if (argc && argv) {
//     
//   }
// }

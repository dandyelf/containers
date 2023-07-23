//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_vector.h"

// externalizing template instances for correct linking, feel free to find more
// information
// template typename s21::Vector<int>;
// template typename s21::Vector<std::string>;

// initializer list constructor (allows creating lists with initializer lists,
// see main.cpp)

template <typename T>
size_t s21::Vector<T>::Size() const noexcept {
  return m_size;
}

template <typename T>
T &s21::Vector<T>::At(size_type i) {
  if (i > m_size) {
    throw std::out_of_range("Index out of range");
  }
  return arr[i];
}

template <typename T>
void s21::Vector<T>::Push_back(value_type v) {
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size * 2);
  }
  arr[m_size++] = v;
}

// template <typename T>
// void s21::Vector<T>::Reserve(size_type new_cap) {
//   if (new_cap <= m_capacity) return;
//   iterator newarr =
//       reinterpret_cast<T *>(new unsigned char[new_cap * sizeof(T)]);
//   size_type i = 0;
//   try {
//     for (; i < m_size; ++i) {
//       new (newarr + i) T(arr[i]);  //  placement new
//     }
//   } catch (...) {
//     for (size_type j = 0; j < i; ++j) {
//       (newarr + j)->~T();
//     }
//     delete[] reinterpret_cast<unsigned char *>(newarr);
//     throw;
//   }
//   for (size_type m = 0; m < m_size; ++m) {
//     (arr + m)->~T();
//   }
//   delete[] reinterpret_cast<unsigned char *>(arr);
//   arr = newarr;
//   m_capacity = new_cap;
// }

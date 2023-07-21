//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_vector.h"

template <typename T>
void s21::Vector<T>::reserve_more_capacity(size_type size) {
  if (size > m_capacity) {
    try {
      value_type *buff = new value_type[size];
      for (size_t i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
      delete[] arr;
      arr = buff;
      m_capacity = size;
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}

// initializer list constructor (allows creating lists with initializer lists,
// see main.cpp)
template <typename T>
s21::Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
};

template <typename T>
size_t s21::Vector<T>::Size() const noexcept {
  return m_size;
}

template <typename T>
T s21::Vector<T>::At(size_type i) {
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
//   if (new_cap < m_capacity) return;
//   iterator newarr =
//       reinterpret_cast<T *>(::new unsigned char[new_cap * sizeof(T)]);
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

// externalizing template instances for correct linking, feel free to find more
// information
template class s21::Vector<int>;

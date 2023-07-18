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
size_t s21::Vector<T>::size() {
  return m_size;
}

template <typename T>
T s21::Vector<T>::at(size_type i) {
  return arr[i];
}

// template <typename T>
// void s21::Vector<T>::push_back(value_type v) {
//   if (m_size == m_capacity) {
//     reserve_more_capacity(m_size * 2);
//   }
//   arr[m_size++] = v;
// }

template <typename T>
void s21::Vector<T>::push_back(value_type v) {
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size * 2);
  }
  arr[m_size++] = v;
}

// externalizing template instances for correct linking, feel free to find more
// information
template class s21::Vector<int>;

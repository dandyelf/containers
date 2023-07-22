//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_vector.h"

#include "s21_matrix_oop.h"

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
s21::Vector<T>::Vector(std::initializer_list<value_type> const &items)
    : Vector(items.size()) {
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

// externalizing template instances for correct linking, feel free to find more
// information
template class s21::Vector<int>;
template class s21::Vector<std::string>;
template class s21::Vector<S21Matrix>;

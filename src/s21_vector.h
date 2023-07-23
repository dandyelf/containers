//
// Created by Left Ranae on 15.04.2023.
//
#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

#include <iostream>

namespace s21 {
template <class T>
class Vector {
  // public attribures
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // public methods
  // default constructor (simplified syntax for assigning values to attributes)
  Vector() {}
  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  // explicit Vector(size_type n)
  //     : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
  Vector(size_type n) : m_size(n), m_capacity(n), arr(nullptr) {
    arr = reinterpret_cast<T *>(new unsigned char[n * sizeof(T)]);
    size_type i = 0;
    try {
      for (; i < n; ++i) {
        new (arr + i) T();  //  placement new
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        (arr + j)->~T();
      }
      delete[] reinterpret_cast<unsigned char *>(arr);
      throw;
    }
  }
  // initializer list constructor (allows creating lists with initializer lists,
  // see main.cpp)
  Vector(std::initializer_list<value_type> const &items);
  // copy constructor with simplified syntax
  Vector(const Vector &v)
      : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {}
  // move constructor with simplified syntax
  Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.arr = nullptr;
    v.m_size = 0;
  };

  // destructor
  ~Vector() {
    for (size_type j = 0; j < m_size; ++j) {
      (arr + j)->~T();
    }
    delete[] reinterpret_cast<unsigned char *>(arr);
  }
  // size getter
  size_type Size() const noexcept;
  // element accessor
  value_type &At(size_type i);
  // capacity getter
  size_type Capacity() const noexcept { return m_capacity; }

  // append new element
  void Push_back(value_type v);
  // rezerv new capacity
  void Reserve(size_type new_cap) {
    if (new_cap <= m_capacity) return;
    iterator newarr =
        reinterpret_cast<T *>(new unsigned char[new_cap * sizeof(T)]);
    size_type i = 0;
    try {
      for (; i < m_size; ++i) {
        new (newarr + i) T(arr[i]);  //  placement new
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        (newarr + j)->~T();
      }
      delete[] reinterpret_cast<unsigned char *>(newarr);
      throw;
    }
    for (size_type m = 0; m < m_size; ++m) {
      (arr + m)->~T();
    }
    delete[] reinterpret_cast<unsigned char *>(arr);
    arr = newarr;
    m_capacity = new_cap;
  }

  void Resise(size_type new_size);

 private:
  // private attributes
  size_type m_size{};
  size_type m_capacity{};
  T *arr{};
  // private method
  void reserve_more_capacity(size_type size);

  // Vector &operator=(Vector &&v) noexcept {
  //   if (this != &v) return *this;
  //   delete this->arr;
  //   this->m_capacity = 0;
  //   this->m_size = 0;
  //   std::swap(this->m_capacity, v.m_capacity);
  //   std::swap(this->m_size, v.m_size);
  //   std::swap(this->arr, v.arr);
  //   return *this;
  // }
};
}  // namespace s21
#endif  // CONTAINERS_SRC_S21_VECTOR_H_

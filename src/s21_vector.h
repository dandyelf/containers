//
// Created by Left Ranae on 15.04.2023.
//
#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

#include <iostream>

namespace s21 {
template <typename T>
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
  explicit Vector(size_type n) : m_size_(n), m_capacity_(n), arr(nullptr) {
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
  // initializer list constructor allows creating lists with initializer lists
  explicit Vector(std::initializer_list<value_type> const &items)
      : Vector(items.size()) {
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
    m_size_ = items.size();
    m_capacity_ = items.size();
  };
  // copy constructor with simplified syntax
  Vector(const Vector &v)
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr(v.arr) {}
  // move constructor with simplified syntax
  Vector(Vector &&v)
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr(v.arr) {
    v.arr = nullptr;
    v.m_size_ = 0;
  };

  // destructor
  ~Vector() {
    for (size_type j = 0; j < m_size_; ++j) {
      (arr + j)->~T();
    }
    delete[] reinterpret_cast<unsigned char *>(arr);
  }
  // size getter
  size_type Size() const noexcept { return m_size_; }
  // element accessor
  T &At(size_type i) {
    if (i > m_size_) {
      throw std::out_of_range("Index out of range");
    }
    return arr[i];
  }
  // capacity getter
  size_type Capacity() const noexcept { return m_capacity_; }

  // append new element
  void Push_back(value_type v) {
    if (m_size_ == m_capacity_) {
      reserve_more_capacity(m_size_ * 2);
    }
    arr[m_size_++] = v;
  }

  // rezerv new capacity
  void Reserve(size_type new_cap) {
    if (new_cap <= m_capacity_) return;
    iterator newarr =
        reinterpret_cast<T *>(new unsigned char[new_cap * sizeof(T)]);
    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
        new (newarr + i) T(arr[i]);  //  placement new
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        (newarr + j)->~T();
      }
      delete[] reinterpret_cast<unsigned char *>(newarr);
      throw;
    }
    for (size_type m = 0; m < m_size_; ++m) {
      (arr + m)->~T();
    }
    delete[] reinterpret_cast<unsigned char *>(arr);
    arr = newarr;
    m_capacity_ = new_cap;
  }

  // void Resise(size_type new_size);

 private:
  // private attributes
  size_type m_size_{};
  size_type m_capacity_{};
  T *arr{};
  // private method
  void reserve_more_capacity(size_type size) {
    if (size > m_capacity_) {
      value_type *buff = new value_type[size];
      for (size_t i = 0; i < m_size_; ++i) buff[i] = std::move(arr[i]);
      delete[] arr;
      arr = buff;
      m_capacity_ = size;
    }
  }

  constexpr Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      std::swap(v.arr, nullptr);
    }
    return *this;
  }
};
}  // namespace s21
#endif  // CONTAINERS_SRC_S21_VECTOR_H_

//
// Created by Left Ranae on 15.04.2023.
//
#ifndef CONTAINERS_SRC_S21_VECTOR_H_
#define CONTAINERS_SRC_S21_VECTOR_H_

#include <cmath>
#include <iostream>
#include <memory>

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
  std::allocator<value_type>
      allocator{};  // Create an object of std::allocator for type T
  // public methods
  // default constructor (simplified syntax for assigning values to attributes)
  Vector() noexcept {}

  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  explicit Vector(size_type n) : m_size_(n), m_capacity_(n), arr(nullptr) {
    if (this->max_size() < m_capacity_) {
      throw std::out_of_range(
          "cannot create s21::vector larger than max_size()");
    }
    CreateVector();
  }

  // initializer list constructor allows creating lists with initializer lists
  Vector(std::initializer_list<value_type> const &items)
      : Vector(items.size()) {
    int i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
      arr[i] = *it;
      i++;
    }
    m_size_ = items.size();
    m_capacity_ = items.size();
  }

  // copy constructor with simplified syntax

  Vector(const Vector &v) : m_size_(v.m_size_), m_capacity_(v.m_capacity_) {
    if (this != &v) {
      std::allocator<value_type>
          allocator;  // Create an object of std::allocator for type T
      using allocator_traits = std::allocator_traits<decltype(allocator)>;

      T *newarr = allocator_traits::allocate(
          allocator, m_capacity_);  // Allocate memory for the new array

      size_type i = 0;
      try {
        for (; i < m_size_; ++i) {
          allocator_traits::construct(
              allocator, newarr + i,
              v.arr[i]);  // Use allocator_traits to construct objects of type T
        }
      } catch (...) {
        for (size_type j = 0; j < i; ++j) {
          allocator_traits::destroy(
              allocator,
              newarr + j);  // Use allocator_traits to destroy objects of type T
        }
        allocator_traits::deallocate(
            allocator, newarr, m_capacity_);  // Deallocate the allocated memory
        throw;
      }
      this->arr = newarr;
    }
  }

  // move constructor with simplified syntax
  Vector(Vector &&v) noexcept
      : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr(v.arr) {
    v.arr = nullptr;
    v.m_size_ = 0;
    v.m_capacity_ = 0;
  };

  ~Vector() {
    std::allocator<T>
        allocator;  // Create an object of std::allocator for type T

    using allocator_traits = std::allocator_traits<decltype(allocator)>;

    for (size_type j = 0; j < m_size_; ++j) {
      allocator_traits::destroy(
          allocator,
          arr + j);  // Use allocator_traits to destroy objects of type T
    }
    allocator_traits::deallocate(
        allocator, arr, m_capacity_);  // Deallocate the allocated memory
  }

  // size getter
  size_type Size() const noexcept { return m_size_; }
  // capacity getter
  size_type Capacity() const noexcept { return m_capacity_; }
  // element accessor
  T &At(size_type i) {
    if (i > m_size_) {
      throw std::out_of_range("Index out of range");
    }
    return arr[i];
  }

  // append new element
  void Push_back(value_type v) {
    if (m_size_ == m_capacity_) {
      try {
        Reserve(m_size_ * 2 + 1);
      } catch (...) {
        throw;
      }
    }
    try {
      new (arr + m_size_) T(v);
    } catch (...) {
      throw;
    }
    ++m_size_;
  }
  // rezerv new capacity
  void Reserve(size_type new_cap) {
    if (new_cap <= m_capacity_) return;

    std::allocator<value_type>
        allocator;  // Create an object of std::allocator for type T
    using allocator_traits = std::allocator_traits<decltype(allocator)>;
    T *newarr = allocator_traits::allocate(
        allocator, new_cap);  // Allocate memory for the new array

    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
        allocator_traits::construct(
            allocator, newarr + i,
            std::move(arr[i]));  // Use allocator_traits to construct objects of
                                 // type T
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        allocator_traits::destroy(
            allocator,
            newarr + j);  // Use allocator_traits to destroy objects of type T
      }
      allocator_traits::deallocate(allocator, newarr,
                                   new_cap);  // Deallocate the allocated memory
      throw;
    }

    for (size_type m = 0; m < m_size_; ++m) {
      allocator_traits::destroy(allocator,
                                arr + m);  // Use allocator_traits to destroy
                                           // objects of type T in the old array
    }
    allocator_traits::deallocate(
        allocator, arr, m_capacity_);  // Deallocate the memory of the old array

    arr = newarr;
    m_capacity_ = new_cap;
  }

  iterator begin() { return &arr[0]; }

  iterator end() { return &arr[m_size_]; }

  const_iterator begin() const {
    const_reference tmp = arr[0];
    return &tmp;
  }

  const_iterator end() const {
    const_reference tmp = arr[0];
    return &tmp;
  }

  size_type max_size() const {
    std::allocator<value_type>
        allocator;  // Create an object of std::allocator for type T
    using allocator_traits = std::allocator_traits<decltype(allocator)>;
    return allocator_traits::max_size(allocator);
  }

 private:
  // private attributes
  size_type m_size_{};
  size_type m_capacity_{};
  T *arr{};
  // private method

  constexpr Vector &operator=(Vector &&v) noexcept {
    if (this != &v) {
      std::swap(v.arr, nullptr);
    }
    return *this;
  }

  void CreateVector() {
    std::allocator<value_type>
        allocator;  // Create an object of std::allocator for type T
    using allocator_traits = std::allocator_traits<decltype(allocator)>;
    T *newarr = allocator_traits::allocate(
        allocator, m_size_);  // Allocate memory for the array

    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
        allocator_traits::construct(
            allocator, newarr + i,
            T());  // Use allocator_traits to construct objects of type T
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        allocator_traits::destroy(
            allocator,
            newarr + j);  // Use allocator_traits to destroy objects of type T
      }
      allocator_traits::deallocate(allocator, newarr,
                                   m_size_);  // Deallocate the allocated memory
      throw;
    }
    arr = newarr;
  }
};  // class Vector
}  // namespace s21

#endif  // CONTAINERS_SRC_S21_VECTOR_H_
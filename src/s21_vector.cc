//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_vector.h"

template <class Iter>
class VectorIterator;

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
      // Create an object of std::allocator for type T
      std::allocator<value_type> allocator;
      // Allocate memory for the new array
      T *newarr = allocator.allocate(m_capacity_);

      size_type i = 0;
      try {
        for (; i < m_size_; ++i) {
          // Use allocator to construct objects of type T
          allocator.construct(newarr + i, v.arr[i]);
        }
      } catch (...) {
        for (size_type j = 0; j < i; ++j) {
          // Use allocator to destroy objects of type T
          allocator.destroy(newarr + j);
        }
        // Deallocate the allocated memory
        allocator.deallocate(newarr, m_capacity_);
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
    // Create an object of std::allocator for type T
    std::allocator<value_type> allocator;
    for (size_type j = 0; j < m_size_; ++j) {
      allocator.destroy(arr + j);  // Use allocator to destroy objects of type T
    }
    allocator.deallocate(arr, m_capacity_);  // Deallocate the allocated memory
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
    T *newarr = reinterpret_cast<T *>(new unsigned char[new_cap * sizeof(T)]);
    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
        new (newarr + i) T(std::move(arr[i]));  //  placement new
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

  // size_type max_size() const {
  //   char bits = 63;
  //   if (sizeof(void *) == 4) {
  //     bits = 31;
  //   }
  //   return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
  // }

  size_type max_size() const {
    std::allocator<value_type> allocator;
    // size_type tmp = allocator.max_size();
    return allocator.max_size();
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
        allocator;  // Создаем объект std::allocator для типа T
    arr = allocator.allocate(m_size_);  // Выделяем память для массива типа T

    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
        allocator.construct(
            arr + i,
            T());  // Используем allocator для конструирования объектов типа T
      }
    } catch (...) {
      for (size_type j = 0; j < i; ++j) {
        allocator.destroy(
            arr + j);  // Используем allocator для уничтожения объектов типа T
      }
      allocator.deallocate(arr, m_size_);  // Освобождаем выделенную память
      throw;
    }
  }
};  // class Vector
}  // namespace s21
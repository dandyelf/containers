//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_vector.h"

namespace s21 {
template <typename T>
class Vector {
  // public attribures
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  // using iterator = T *;
  // using const_iterator = const T *;
  using size_type = size_t;
  // public methods
  // default constructor (simplified syntax for assigning values to attributes)
  Vector() {}

  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  Vector(size_type n) : m_size_(n), m_capacity_(n), arr(nullptr) {
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
      CreateVector();
    }
    // std::memcpy(matrix_[i], other_p[i], (cols_ * sizeof(double)));
  }

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
      try {
        Reserve(m_size_ * 2 + 1);
        new (arr + m_size_) T(v);  //  placement new
      } catch (...) {
        throw;
      }
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

 private:
  // private attributes
  size_type m_size_{};
  size_type m_capacity_{};
  T *arr{};
  template <class Iter>
  class VectorIterator {
    friend class Vector;

   public:
    typedef Iter iterator_type;
    typedef std::input_iterator_tag iterator_category;
    typedef iterator_type value_type;
    typedef ptrdiff_t difference_type;
    typedef iterator_type &reference;
    typedef iterator_type *pointer;
    iterator_type *value;

   private:
    VectorIterator(Iter *p) : value(p) {}

   public:
    VectorIterator(const VectorIterator &it) : value(it.value) {}
  };  //  class Iter

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

  void CreateVector() {
    arr = reinterpret_cast<T *>(new unsigned char[m_size_ * sizeof(T)]);
    size_type i = 0;
    try {
      for (; i < m_size_; ++i) {
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

 public:
  typedef VectorIterator<Vector> iterator;
  typedef VectorIterator<Vector> const_iterator;

  iterator begin() { return arr[0]; }
  iterator end() { return iterator(nullptr); }
};
}  // namespace s21
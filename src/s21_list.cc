//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_list.h"

namespace s21 {
template <typename T>
class List {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  // public attribures
 public:
 private:
  struct Node {
    value_type value_;
    Node* prev_;
    Node* next_;

    Node(const value_type& value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

 public:
  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    reference operator*() {
      if (!this->ptr_) {
        throw std::invalid_argument("Value is nullptr");
      }
      return this->ptr_->value_;
    }

    ListIterator operator++(int) {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator operator--(int) {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator& operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator& operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->next_;
      }

      ListIterator res(tmp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->prev_;
      }
      ListIterator res(tmp);
      return res;
    }
    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_ = nullptr;
    friend class List<T>;
  };

  using iterator = ListIterator<T>;
  //   using const_iterator = ListConstIterator<T>;
};  // class List
}  // namespace s21

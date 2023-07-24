//
// Created by Left Ranae on 15.04.2023.
//
#ifndef CONTAINERS_SRC_S21_STACK_H_
#define CONTAINERS_SRC_S21_STSCK_H_

#include <iomanip>
#include <iostream>

template <typename T>
class Stack {
 private:
  T *stackPtr;  // указатель на стек
  int size;     // размер стека
  T top;        // вершина стека
 public:
  Stack(int = 10);  // по умолчанию размер стека равен 10 элементам
  ~Stack();         // деструктор
  bool push(const T);  // поместить элемент в стек
  bool pop();          // удалить из стека элемент
  void printStack();
};

// конструктор
template <typename T>
Stack<T>::Stack(int s) {
  size = s > 0 ? s : 10;  // инициализировать размер стека
  stackPtr = new T[size];  // выделить память под стек
  top = -1;  // значение -1 говорит о том, что стек пуст
}

// деструктор
template <typename T>
Stack<T>::~Stack() {
  delete[] stackPtr;  // удаляем стек
}

// элемент функция класса  Stack для помещения элемента в стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, элемент в стек не добавлен
template <typename T>
bool Stack<T>::push(const T value) {
  if (top == size - 1) return false;  // стек полон

  top++;
  stackPtr[top] = value;  // помещаем элемент в стек

  return true;  // успешное выполнение операции
}

// элемент функция класса  Stack для удаления элемента из стек
// возвращаемое значение - true, операция успешно завершена
//                                    false, стек пуст
template <typename T>
bool Stack<T>::pop() {
  if (top == -1) return false;  // стек пуст

  stackPtr[top] = 0;  // удаляем элемент из стека
  top--;

  return true;  // успешное выполнение операции
}

// вывод стека на экран
template <typename T>
void Stack<T>::printStack() {
  for (int ix = size - 1; ix >= 0; ix--)
    std::cout << "|" << std::setw(4) << stackPtr[ix] << std::endl;
}

#endif  // CONTAINERS_SRC_S21_STACK_H_
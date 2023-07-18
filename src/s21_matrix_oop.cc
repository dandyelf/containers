//
// Created by Left Ranae on 15.04.2023.
//

#include "s21_matrix_oop.h"

#include <cmath>
#include <cstring>
#include <iostream>

S21Matrix::S21Matrix() {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Rows and cols must be not <= 0");
  CreateMatrix();
}

void S21Matrix::CreateMatrix() {
  if (rows_ != 0 && cols_ != 0) {
    matrix_ = new double *[rows_] {};
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (this != &other) {
    CreateMatrix();
    CopyMatrix(other.matrix_);
  }
}

void S21Matrix::CopyMatrix(double **other_p) {
  if (matrix_ && other_p)
    for (int i = 0; i < rows_; i++) {
      std::memcpy(matrix_[i], other_p[i], (cols_ * sizeof(double)));
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  RemoveMatrix();
  SwapObj(other);
}

void S21Matrix::SwapObj(S21Matrix &other) {
  int tmp = rows_;
  rows_ = other.rows_;
  other.rows_ = tmp;
  tmp = cols_;
  cols_ = other.cols_;
  other.cols_ = tmp;
  double **tmp1 = matrix_;
  matrix_ = other.matrix_;
  other.matrix_ = tmp1;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix res(other);
  SwapObj(res);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other) return *this;
  RemoveMatrix();
  SwapObj(other);
  return *this;
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw std::invalid_argument("Rows and cols must be not <= 0");
  S21Matrix tmp(rows, cols_);
  if (rows == rows_) {
  } else if (rows < rows_) {
    SwapObj(tmp);
    CopyMatrix(tmp.matrix_);
  } else {
    SwapObj(tmp);
    for (int i = 0; i < tmp.rows_; i++) {
      std::memcpy(matrix_[i], tmp.matrix_[i], (cols_ * sizeof(double)));
    }
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw std::invalid_argument("Rows and cols must be <= 0");
  S21Matrix tmp(rows_, cols);
  if (cols == cols_) {
  } else if (cols < cols_) {
    SwapObj(tmp);
    CopyMatrix(tmp.matrix_);
  } else {
    SwapObj(tmp);
    for (int i = 0; i < rows_; i++) {
      std::memcpy(matrix_[i], tmp.matrix_[i], (tmp.cols_ * sizeof(double)));
    }
  }
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  if (row < 0 || col < 0) {
    throw std::out_of_range("Index must be <= 0");
  }
  return matrix_[row][col];
}

const double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  if (row < 0 || col < 0) {
    throw std::out_of_range("Index must be <= 0");
  }
  return matrix_[row][col];
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (&other == this) return 1;
  bool eq_matr{};
  if (SizeEq(other)) eq_matr = EqArr(other);
  return eq_matr;
}

bool S21Matrix::SizeEq(const S21Matrix &other) const {
  return (rows_ == other.rows_ && cols_ == other.cols_);
}

bool S21Matrix::EqArr(const S21Matrix &other) const {
  bool eq_arr = true;
  for (int i = 0; i < rows_ && eq_arr; i++) {
    for (int j = 0; j < cols_ && eq_arr; j++) {
      if (!(std::fabs(matrix_[i][j] - other.matrix_[i][j]) < EPS)) {
        eq_arr = false;
      }
    }
  }
  return eq_arr;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!SizeEq(other)) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  SumSubMatr(other.matrix_, '+');
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix matr(*this);
  matr.SumMatrix(other);
  return matr;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!SizeEq(other)) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  SumSubMatr(other.matrix_, '-');
}

void S21Matrix::SumSubMatr(double **const &other_p, char oper) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (oper == '+')
        matrix_[i][j] = matrix_[i][j] + other_p[i][j];
      else
        matrix_[i][j] = matrix_[i][j] - other_p[i][j];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix matr(*this);
  matr.SubMatrix(other);
  return matr;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix matr(*this);
  matr.MulNumber(num);
  return matr;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) throw std::out_of_range("cols mast be equal rows");
  S21Matrix matr(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.cols_; ++j)
      for (int k = 0; k < cols_; ++k)
        matr.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  SwapObj(matr);
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix matr(*this);
  matr.MulMatrix(other);
  return matr;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix matr(cols_, rows_);
  for (int i = 0; i < matr.rows_; i++)
    for (int j = 0; j < matr.cols_; j++) {
      matr.matrix_[i][j] = matrix_[j][i];
    }
  SwapObj(matr);
  return *this;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::invalid_argument("Rows and coloumns mast be the same");
  S21Matrix complement(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      complement(i, j) = CalcMinor(i, j) * pow(-1, i + j);
  return complement;
}

double S21Matrix::CalcMinor(int row, int col) {
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  int tmp_row{}, tmp_col{};
  for (int i = 0; i < rows_; i++) {
    if (i == row) continue;
    for (int j = 0; j < cols_; j++) {
      if (j == col) continue;
      tmp.matrix_[tmp_row][tmp_col] = matrix_[i][j];
      tmp_col++;
    }
    tmp_col = 0;
    tmp_row++;
  }
  return tmp.CalcDeterminant();
}

double S21Matrix::Determinant() {
  if (rows_ != cols_)
    throw std::invalid_argument("Rows and coloumns mast be the same");
  return CalcDeterminant();
}

double S21Matrix::CalcDeterminant() {
  double det{};
  if (rows_ == 1)
    det = matrix_[0][0];
  else if (rows_ == 2)
    det = DETERMIN2x2();
  else if (rows_ == 3)
    det = DETERMIN3x3();
  else
    for (int j = 0; j < cols_; j++) {
      det += CalcMinor(0, j) * pow(-1, j) * matrix_[0][j];
    }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) throw std::runtime_error("Determinant is 0");
  S21Matrix complem;
  if (cols_ == 1 && rows_ == 1) {
    complem = *this;
    complem(0, 0) = 1 / det;
  } else {
    S21Matrix trans = Transpose();
    complem = trans.CalcComplements();
    complem.MulNumber(1 / det);
  }
  return complem;
}

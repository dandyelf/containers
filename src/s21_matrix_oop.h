//
// Created by Left Ranae on 15.04.2023.
//

#ifndef CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H_

constexpr double EPS = 10E-9;

class S21Matrix {
 public:
  // constructors
  S21Matrix();                            // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy constructor
  S21Matrix(S21Matrix&& other) noexcept;  // move constructor
  ~S21Matrix();                           // destructor

  // accessor и mutator. При увеличении размера - матрица дополняется нулевыми
  // элементами, при уменьшении - лишнее просто отбрасывается
  inline int GetRows() const noexcept { return rows_; };  // accessor  for rows
  inline int GetCols() const noexcept { return cols_; };  // accessor for cols
  void SetRows(int rows);                                 // mutator for rows
  void SetCols(int cols);                                 // mutator for cols

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& other);       // assignment operator overload
  double& operator()(int row, int col);          // index operator overload
  const double& operator()(int row, int col) const;  // index const overload
  bool operator==(const S21Matrix& other) const;     // eq operator overload
  S21Matrix operator+(const S21Matrix& other);       // sum operator overload
  S21Matrix operator-(const S21Matrix& other);       // sub operator overload
  S21Matrix operator*(const double num);        // mul number operator overload
  S21Matrix operator*(const S21Matrix& other);  // mul matrix operator overload

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);

  // some public methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();        //  transponse matrix
  S21Matrix CalcComplements();  //  algebraic addition matrix
  double Determinant();         //  matrix determinant
  S21Matrix InverseMatrix();    // inverse matrix

 private:
  // attributes
  int rows_{}, cols_{};  // rows and columns attributes
  double** matrix_{};    // pointer to the memory where the matrix

  // private metods
  void CreateMatrix();
  void RemoveMatrix();
  void CopyMatrix(double** other_p);
  void SwapObj(S21Matrix& other);
  bool SizeEq(const S21Matrix& other) const;
  bool EqArr(const S21Matrix& other) const;
  void SumSubMatr(double** const& other_p, char oper);
  double CalcMinor(int row, int col);
  double CalcDeterminant();
  inline double DETERMIN2x2() {
    return matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  }
  inline double DETERMIN3x3() {
    return matrix_[0][0] * matrix_[1][1] * matrix_[2][2] -
           matrix_[0][0] * matrix_[1][2] * matrix_[2][1] -
           matrix_[0][1] * matrix_[1][0] * matrix_[2][2] +
           matrix_[0][1] * matrix_[1][2] * matrix_[2][0] +
           matrix_[0][2] * matrix_[1][0] * matrix_[2][1] -
           matrix_[0][2] * matrix_[1][1] * matrix_[2][0];
  }
};

#endif  // CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H_

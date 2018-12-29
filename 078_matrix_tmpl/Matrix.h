#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows() {}
  Matrix(int r, int c);
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}
  ~Matrix() {}

  int getRows() const { return this->numRows; }
  int getColumns() const { return this->numColumns; }

  Matrix<T> & operator=(const Matrix<T> rhs);
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
  template<typename X>
  friend std::ostream & operator<<(std::ostream & stream, const Matrix<X> & matrix);
};

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows() {
  rows.resize(numRows);
  for (int i = 0; i < numRows; i++) {
    rows[i].resize(numColumns);
  }
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> rhs) {
  if (this != &rhs) {
    std::vector<std::vector<T> > temp;
    temp = rhs.rows;
    this->numRows = rhs.numRows;
    this->numColumns = rhs.numColumns;
    this->rows = temp;
  }
  return *this;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(0 <= index && index < numRows);
  return this->rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(0 <= index && index < numRows);
  return this->rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns || rows != rhs.rows) {
    return false;
  }
  else {
    return true;
  }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(rhs.getColumns() == this->getColumns() && rhs.getRows() == this->getRows());

  Matrix<T> answer = *this;
  for (int i = 0; i < getRows(); i++) {
    for (int j = 0; j < getColumns(); j++) {
      answer[i][j] = answer[i][j] + rhs[i][j];
    }
  }

  return answer;
}

template<typename T>
std::ostream & operator<<(std::ostream & stream, const Matrix<T> & matrix) {
  stream << "[ ";
  for (int i = 0; i < matrix.getRows(); i++) {
    if (i != 0) {
      stream << ",\n{";
    }
    else {
      stream << "{";
    }
    for (int j = 0; j < matrix.getColumns(); j++) {
      if (j != 0) {
        stream << ", ";
      }
      stream << matrix[i][j];
    }
    stream << "}";
  }

  stream << " ]";
  return stream;
}

#endif

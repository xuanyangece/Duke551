#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(NULL) {
  //  std::cout << "self const";
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.getRows()),
    numColumns(rhs.getColumns()),
    rows(NULL) {
  //std::cout << "use copy cons";
  rows = new IntArray *[rhs.getRows()];
  for (int i = 0; i < rhs.getRows(); i++) {
    rows[i] = new IntArray(rhs.getColumns());
    *rows[i] = rhs[i];
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < getRows(); i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  //std::cout << "use =";
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.getRows()];
    for (int i = 0; i < rhs.getRows(); i++) {
      temp[i] = new IntArray(rhs.getColumns());
      *(temp[i]) = rhs[i];
    }

    for (int i = 0; i < this->getRows(); i++) {
      delete this->rows[i];
    }
    delete[] this->rows;

    this->rows = temp;
    this->numColumns = rhs.getColumns();
    this->numRows = rhs.getRows();
  }

  return *this;
}

int IntMatrix::getRows() const {
  return this->numRows;
}

int IntMatrix::getColumns() const {
  return this->numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < this->numRows);
  return *(rows[index]);
}

IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < this->numRows);
  return *(rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (rhs.getColumns() != this->getColumns() || rhs.getRows() != this->getRows()) {
    return false;
  }
  for (int i = 0; i < this->getRows(); i++) {
    if (*this->rows[i] != rhs[i]) {
      return false;
    }
  }

  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(rhs.getColumns() == this->getColumns() || rhs.getRows() == this->getRows());

  IntMatrix res = *this;
  //  std::cout << "+, row:" << res.getRows() << " column:" << res.getColumns() << std::endl;

  for (int i = 0; i < this->getRows(); i++) {
    for (int j = 0; j < this->getColumns(); j++) {
      res[i][j] = res[i][j] + rhs[i][j];
    }
  }

  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i < rhs.getRows() - 1) {
      s << ",\n";
    }
  }

  s << " ]";
  return s;
}

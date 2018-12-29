#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(NULL), numElements(n) {
  data = new int[n];
  for (int i = 0; i < n; i++) {
    data[i] = 0;
  }
}

IntArray::IntArray(const IntArray & rhs) : data(NULL), numElements(rhs.size()) {
  data = new int[numElements];
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    // only need new data
    int * temp = new int[rhs.size()];
    for (int i = 0; i < rhs.size(); i++) {
      temp[i] = rhs.data[i];
    }

    // delete original
    delete[] data;
    data = temp;
    numElements = rhs.numElements;
  }

  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 || index < numElements);

  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index >= 0 || index < numElements);

  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return false;
  }
  else {
    for (int i = 0; i < this->numElements; i++) {
      if (this->data[i] != rhs.data[i]) {
        return false;
      }
    }
  }

  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !((*this) == (rhs));
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << '{';

  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }

  s << '}';

  return s;
}

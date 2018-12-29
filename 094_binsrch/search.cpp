#include <cmath>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int left = low;
  int right = high;
  int mid = 0;
  int ret = 0;

  while (left < right) {
    mid = left + (right - left) / 2;
    ret = f->invoke(mid);
    if (ret == 0)
      return mid;
    else if (ret < 0) {
      left = mid + 1;
    }
    else {
      right = mid;
    }
  }

  // all possible
  if (left == low)
    return left;
  else
    return left - 1;
}

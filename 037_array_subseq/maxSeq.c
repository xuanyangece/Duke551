#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t sum = 0;

  if (n > 0) {
    size_t currentSum = 1;
    sum = 1;

    for (int i = 0; i < n - 1; i++) {
      if (*(array + i) < *(array + i + 1)) {
        currentSum++;
      }
      else {
        if (sum < currentSum) {
          sum = currentSum;
        }
        currentSum = 1;
      }
    }

    // last time check
    if (sum < currentSum) {
      sum = currentSum;
    }
  }

  return sum;
}

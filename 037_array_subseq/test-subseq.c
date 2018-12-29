#include <stdio.h>
#include <stdlib.h>

// proto
size_t maxSeq(int * array, size_t n);

void testMS(int * array, size_t n, size_t expected) {
  if (maxSeq(array, n) != expected) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[5] = {1, 2, 3, 4, 5};
  testMS(array1, 5, 5);

  int array2[1] = {0};
  testMS(array2, 1, 1);

  int array3[0] = {};
  testMS(array3, 0, 0);

  int array4[4] = {4, 3, 2, 1};
  testMS(array4, 4, 1);

  int array5[8] = {2, 2, -1, 3, 4, 5, 0, 2};
  testMS(array5, 8, 4);

  int array6[20000] = {1, 400, -2000, 20000, 65536};
  testMS(array6, 20000, 3);

  int array7[65536] = {0};
  testMS(array7, 65536, 1);

  int array8[3] = {1, 0, 1};
  testMS(array8, 3, 2);

  return EXIT_SUCCESS;
}

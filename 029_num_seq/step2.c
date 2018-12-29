// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return x + (x + 1) * (x + 1);
}

int sumSeq2(int low, int high) {
  int res = 0;
  for (int i = low; i < high; i++) {
    res += seq2(i);
  }

  return res;
}

int main(void) {
  // test seq2
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", 100, seq2(100));
  printf("seq2(%d) = %d\n", -100, seq2(-100));
  printf("seq2(%d) = %d\n", 5000, seq2(5000));

  // test sumSeq2
  printf("sumSeq2(%d, %d) = %d\n", 0, 0, sumSeq2(0, 0));
  printf("sumSeq2(%d, %d) = %d\n", 100, 500, sumSeq2(100, 500));
  printf("sumSeq2(%d, %d) = %d\n", -200, -30, sumSeq2(-200, -30));
  printf("sumSeq2(%d, %d) = %d\n", -1, 330, sumSeq2(-1, 330));

  return EXIT_SUCCESS;
}

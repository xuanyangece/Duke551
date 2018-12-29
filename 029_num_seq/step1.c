// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}

void printSeq1Range(int low, int high) {
  for (int i = low; i < high; i++) {
    printf("%d", seq1(i));
    if (i < high - 1) {
      printf(", ");
    }
  }

  printf("\n");
}

int main(void) {
  // test seq1
  printf("seq1(%d) = %d\n", 1, seq1(1));
  printf("seq1(%d) = %d\n", 200, seq1(200));
  printf("seq1(%d) = %d\n", 3000, seq1(3000));
  printf("seq1(%d) = %d\n", 0, seq1(0));
  printf("seq1(%d) = %d\n", -1, seq1(-1));
  printf("seq1(%d) = %d\n", -300, seq1(-300));

  // test printSe1Range
  printf("printSeq1Range(%d, %d)\n", 1, 2);
  printSeq1Range(1, 2);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1Range(%d, %d)\n", 100, -11);
  printSeq1Range(100, -11);
  printf("printSeq1Range(%d, %d)\n", -20, 2000);
  printSeq1Range(-20, 2000);
  printf("printSeq1Range(%d, %d)\n", -500, 0);
  printSeq1Range(-500, 0);

  return EXIT_SUCCESS;
}

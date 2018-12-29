// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return (-3) * x + y * (x + 2);
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int res = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0) {
        res++;
      }
    }
  }

  return res;
}

int main(void) {
  // test seq3
  printf("seq3(%d, %d) = %d\n", -5, -2, seq3(-5, -2));
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(-0, 0));
  printf("seq3(%d, %d) = %d\n", -50, 100, seq3(-50, 100));
  printf("seq3(%d, %d) = %d\n", 200, 1, seq3(200, 1));

  // countEvenInSea3Range
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         5,
         20,
         7,
         0,
         countEvenInSeq3Range(5, 20, 7, 0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         0,
         3,
         -20,
         100,
         countEvenInSeq3Range(0, 3, -20, 100));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 5, 7, 5, 7, countEvenInSeq3Range(5, 7, 5, 7));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         -1,
         -2,
         -3,
         -4,
         countEvenInSeq3Range(-1, -2, -3, -4));

  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int testIt(unsigned a, unsigned b, unsigned expect) {
  if (power(a, b) != expect) {
    exit(EXIT_FAILURE);
  }
  else
    return 1;
}

int main(void) {
  testIt(0, 0, 1);
  testIt(1, 1, 1);
  testIt(2, 4, 16);
  testIt(100, 2, 10000);
  testIt(200, 1, 200);
  testIt(65535, 1, 65535);
  testIt(2, 10, 1024);
  testIt(1, 0, 1);
  testIt(400, 2, 160000);
  testIt(1, 9, 1);

  return EXIT_SUCCESS;
}

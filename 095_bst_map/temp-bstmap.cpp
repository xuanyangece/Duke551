#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> m1;
  m1.BstMap<int, int>::add(11, 2);
  assert(m1.lookup(11) == 2);
  m1.add(7, 1);
  m1.add(3, 1);
  m1.add(1, 1);
  m1.add(9, 1);
  m1.add(10, 1);
  m1.add(4, 1);
  m1.add(8, 1);
  m1.add(5, 5);

  int input[] = {3, 1, -23, 4, 7, 9, 88, 17, 44, 77};
  for (int i = 0; i < 10; i++) {
    m1.add(input[i], 10);
  }

  m1.remove(7);
  m1.remove(5);
  m1.remove(7);
  m1.remove(5);
  m1.remove(9);
  m1.remove(3);
  m1.remove(1);
  m1.remove(9);
  m1.remove(10);
  m1.remove(4);
  m1.remove(8);
  m1.remove(5);
  for (int i = 0; i < 10; i++) {
    m1.remove(input[i]);
  }

  return EXIT_SUCCESS;
}

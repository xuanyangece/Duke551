#include <cmath>
#include <cstdlib>
#include <iostream>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class NormalFunction1 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg * 200 - 600; }
};

class NormalFunction2 : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg / 100 + 2; };
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  unsigned limit = (low == high) ? 1 : log2(high - low) + 1;

  Function<int, int> * test = new CountedIntFn(limit, f, mesg);

  int answer = binarySearchForZero(test, low, high);
  if (answer != expected_ans) {
    fprintf(stderr, "Invalid answer\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  Function<int, int> * f1 = new SinFunction();
  check(f1, 0, 150000, 52359, "error");

  check(f1, 1000, 2000, 1999, "rr");

  check(f1, -20000, 10000, 9999, "err");

  check(f1, 70000, 2000000, 1308996, "aa");

  check(f1, -147483648, 147483648, 73565627, "xz");

  Function<int, int> * f2 = new NormalFunction1();
  check(f2, 3, 5, 3, "error");

  check(f2, -5, 9, 3, "error");

  check(f2, 5, 5, 5, "error");

  check(f2, 3, 3, 3, "error");

  check(f2, 5, 100, 5, "error");  // positive

  check(f2, -20, -10, -11, "error");  // negative

  check(f2, -200, 100, 3, "error");

  Function<int, int> * f3 = new NormalFunction2();

  check(f3, -200, -200, -200, "e");

  check(f3, -20, -10, -20, "e");

  check(f3, -2000, -1000, -1001, "e");

  check(f3, 5000, 7000, 5000, "e");

  check(f2, 1, 0, 1, "e");

  return EXIT_SUCCESS;
}

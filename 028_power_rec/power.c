// I used to do this on Leetcode
unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  return (y % 2 == 0) ? power(x * x, y / 2) : x * power(x * x, y / 2);
}

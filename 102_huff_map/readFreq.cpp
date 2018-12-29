#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream file(fname);
  if (!file) {
    std::cerr << "shit";
    exit(EXIT_FAILURE);
  }

  // array
  uint64_t * answer = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    answer[i] = 0;
  }

  // read file by character
  char c = ' ';
  while (file.get(c)) {
    int index = (unsigned char)c;
    answer[index] += 1;
  }

  answer[256] = 1;

  file.close();

  return answer;
}

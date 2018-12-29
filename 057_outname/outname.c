#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  if (inputName == NULL) {
    perror("invalid input");
    exit(EXIT_FAILURE);
  }

  // calculate length
  size_t length = 0;
  const char * reader = inputName;
  while (*(reader + length) != '\0') {
    length++;
  }

  // .counts + \0
  //  length += 8;

  char * res = malloc(sizeof(*res) * (length + 8));
  char post[8] = {'.', 'c', 'o', 'u', 'n', 't', 's', '\0'};

  for (size_t i = 0; i < length; i++) {
    res[i] = reader[i];
  }

  for (size_t i = 0; i < 8; i++) {
    res[length + i] = post[i];
  }

  return res;
}

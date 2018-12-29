
#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readLine(kvpair_t * pair, const char * line) {
  const char * reader = line;

  // use a fixed pattern maybe revised later
  pair->key = NULL;
  pair->value = NULL;

  // get length of key & value
  char * klen = strchr(line, '=');
  pair->key = malloc(sizeof(*pair->key) * (klen - line + 1));
  size_t vlen = strlen(line) - (klen - line);
  pair->value = malloc(sizeof(*pair->value) * vlen);
  // read key
  int oldPosition = 0;
  while (*(reader + oldPosition) != '=') {
    if (*(reader + oldPosition) == '\n') {
      printf("not valid kv");
      exit(EXIT_FAILURE);
    }
    pair->key[oldPosition] = *(reader + oldPosition);
    oldPosition++;
  }
  pair->key[oldPosition] = '\0';
  // skip=
  oldPosition++;

  // read value
  int newPosition = 0;
  while (*(reader + oldPosition) != '\n') {
    pair->value[newPosition] = *(reader + oldPosition);
    oldPosition++;
    newPosition++;
  }
  pair->value[newPosition] = '\0';

  // test code
  //printf("the key is: %s\n", pair->key);
  //printf("the value is: %s\n", pair->value);
}

kvarray_t * readKVs(const char * fname) {
  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("cannot open file");
    exit(EXIT_FAILURE);
  }

  // define result array
  kvarray_t * pairs = malloc(sizeof(*pairs));
  pairs->length = 0;
  pairs->kv = NULL;

  // read from line to line
  kvpair_t * temp = NULL;
  size_t n = 0;

  char * p = NULL;
  size_t sz = 0;
  while (getline(&p, &sz, f) >= 0) {
    temp = realloc(temp, sizeof(*temp) * (n + 1));

    readLine(&temp[n], p);
    free(p);
    p = NULL;
    n++;
  }
  free(p);
  // added
  p = NULL;

  // close file
  if (fclose(f) != 0) {
    perror("cannot close");
    exit(EXIT_FAILURE);
  }

  // return
  pairs->kv = temp;
  pairs->length = n;
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->kv[i].key);
    pairs->kv[i].key = NULL;
    free(pairs->kv[i].value);
    pairs->kv[i].value = NULL;
  }
  free(pairs->kv);
  pairs->kv = NULL;
  free(pairs);
  pairs = NULL;
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kv[i].key, pairs->kv[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  char * res = NULL;
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(key, pairs->kv[i].key) == 0) {
      res = pairs->kv[i].value;
    }
  }
  return res;
}

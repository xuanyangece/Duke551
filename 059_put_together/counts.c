#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  // define
  /* AAAAAAAAAALOCATE 1*/
  counts_t * res = malloc(sizeof(*res));
  // initialize
  res->length = 0;
  res->arrayc = NULL;
  res->unknowns = 0;

  // test code
  //  printf("new counts initialized\n");
  return res;
}

void addCount(counts_t * c, const char * name) {
  if (c == NULL) {
    exit(EXIT_FAILURE);
  }

  // unknowns
  if (name == NULL) {
    c->unknowns++;

    // test code
    // printf("add unknown %ld\n", c->unknowns);
    return;
  }
  // normal
  else {
    // check if there
    // assume is
    for (size_t i = 0; i < c->length; i++) {
      if (strcmp(c->arrayc[i].name, name) == 0) {
        c->arrayc[i].count++;

        //test code
        // printf("now the No.%ld name is %s\n", i, name);
        // printf("and the count is %ld\n", c->arrayc[i].count);
        return;
      }
    }

    // no, create new one
    /* AAAAAAAAAAAAAALOCATE 2 */
    c->arrayc = realloc(c->arrayc, sizeof(*c->arrayc) * (c->length + 1));
    c->arrayc[c->length].count = 1;
    /* AAAAAAAAAAAAAALOCATE 3 */
    c->arrayc[c->length].name = malloc(sizeof(*c->arrayc[c->length].name) * (strlen(name) + 1));

    // cpystr
    size_t curr = 0;
    const char * reader = name;
    while (*(reader + curr) != '\0') {
      c->arrayc[c->length].name[curr] = *(reader + curr);
      curr++;
    }
    c->arrayc[c->length].name[curr] = '\0';

    //test code
    // printf("new name added: %s\nin No.%ld\n", name, c->length);
    c->length++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  // print normal
  for (size_t i = 0; i < c->length; i++) {
    // printf("%s: %ld\n", c->arrayc[i].name, c->arrayc[i].count);
    fprintf(outFile, "%s: %ld\n", c->arrayc[i].name, c->arrayc[i].count);
  }
  // print unknown if have
  if (c->unknowns > 0) {
    // printf("<unknown> : %ld\n", c->unknowns);
    fprintf(outFile, "<unknown> : %ld\n", c->unknowns);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->length; i++) {
    free(c->arrayc[i].name);
    c->arrayc[i].name = NULL;
  }
  free(c->arrayc);
  c->arrayc = NULL;
  free(c);
  c = NULL;
}

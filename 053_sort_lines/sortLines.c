#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortFile(FILE * f) {
  char ** strs = NULL;
  size_t strc = 0;

  char * p = NULL;
  size_t sz = 0;
  while (getline(&p, &sz, f) >= 0) {
    strs = realloc(strs, sizeof(*strs) * (strc + 1));
    strs[strc] = p;
    p = NULL;
    strc++;
  }
  free(p);
  // sort data
  sortData(strs, strc);

  // free memory

  for (size_t i = 0; i < strc; i++) {
    printf("%s", strs[i]);
    free(strs[i]);
  }
  free(strs);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    char ** strs = NULL;
    size_t strc = 0;

    char * p = NULL;
    size_t sz = 0;
    while (getline(&p, &sz, stdin) >= 0) {
      strs = realloc(strs, sizeof(*strs) * (strc + 1));

      strs[strc] = p;
      p = NULL;
      strc++;
    }
    free(p);
    // sort
    sortData(strs, strc);

    // must free p after sort

    // free memory
    for (size_t i = 0; i < strc; i++) {
      printf("%s", strs[i]);
      free(strs[i]);
    }
    free(strs);
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("cannot open file");
        exit(EXIT_FAILURE);
      }
      sortFile(f);
      if (fclose(f) != 0) {
        perror("cannot close file");
        exit(EXIT_FAILURE);
      }
    }
  }
  //WRITE YOUR CODE HERE!

  return EXIT_SUCCESS;
}

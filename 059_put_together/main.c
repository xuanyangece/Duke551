#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  if (filename == NULL) {
    perror("invalid file name");
    exit(EXIT_FAILURE);
  }

  // define result and init
  counts_t * counts = createCounts();

  // open file
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("cannot open file");
    exit(EXIT_FAILURE);
  }

  // read
  char * p = NULL;
  size_t sz = 0;
  ssize_t llen = 0;
  // AAAAAAALOCATE 1
  while ((llen = getline(&p, &sz, f)) >= 0) {
    p[llen - 1] = '\0';

    addCount(counts, lookupValue(kvPairs, p));
  }
  free(p);
  p = NULL;

  // close file
  if (fclose(f) != 0) {
    perror("cannot close file");
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {
    perror("invalid argument number");
    exit(EXIT_FAILURE);
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = NULL;
  kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    counts_t * c = NULL;
    char * outName = NULL;
    FILE * f = NULL;
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    f = fopen(outName, "w");
    if (f == NULL) {
      perror("cannot write file");
      exit(EXIT_FAILURE);
    }

    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    if (fclose(f) != 0) {
      exit(EXIT_FAILURE);
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    outName = NULL;
    c = NULL;
  }
  //free the memory for kv
  freeKVs(kv);
  kv = NULL;

  return EXIT_SUCCESS;
}

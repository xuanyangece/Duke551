#include <stdio.h>
#include <stdlib.h>

// func

int main(int argc, char ** argv) {
  // condition check
  if (argc != 2 || argv == NULL) {
    fprintf(stderr, "Usage: file inputFileName!");
    return EXIT_FAILURE;
  }

  char original[10][10];
  char post[10][10];

  // read file
  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file!");
    return EXIT_FAILURE;
  }

  int c = 0;
  int total = 0;
  int count = 0;
  int i = 0;  // row
  int j = 0;  // column
  while ((c = fgetc(f)) != EOF) {
    char curr = 'a' + (c - 'a');
    if (count % 10 != 0 && curr == '\n') {
      fprintf(stderr, "Invalid matrix");
      return EXIT_FAILURE;
    }

    if (curr == '\n') {
      count = 0;
      i++;
      j = 0;
      continue;
    }
    original[i][j] = curr;
    count++;
    j++;
    total++;
  }

  if (total != 100) {
    fprintf(stderr, "Invalid matrix");
    return EXIT_FAILURE;
  }

  // convert to new char[][]
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      post[i][j] = original[j][9 - i];
    }
  }

  char post2[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      post2[i][j] = post[9 - j][9 - i];
    }
  }

  // fprintf ** REVERSE
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", post2[j][i]);
      if (j == 9) {
        fprintf(stdout, "\n");
      }
    }
  }

  if (fclose(f) != 0) {
    perror("Failed to close file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

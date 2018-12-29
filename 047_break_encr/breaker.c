#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// countFre
char countFre(FILE * F) {
  int result[26] = {0};

  // get frequency
  int c = 0;
  while ((c = fgetc(F)) != EOF) {
    if (isalpha(c)) {
      int diff = c - 'a';
      result[diff]++;
    }
  }

  int max = 0;
  int indice = -1;
  // back map to get E
  for (int i = 0; i < 26; i++) {
    if (max < result[i]) {
      indice = i;
      max = result[i];
    }
  }

  /* handled indice = -1 0 */
  if (indice == -1) {
    exit(EXIT_FAILURE);
  }

  char ourE = 'a' + indice;
  return ourE;
}

// getKey
int getKey(char ourE) {
  int i = ourE - 'e';
  if (i < 0) {
    i = 26 + i;
  }
  return i;
}

int main(int argc, char ** argv) {
  if (argc != 2 || argv[1] == NULL) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  /* handle numbers empty */

  // open file
  FILE * F = fopen(argv[1], "r");
  if (F == NULL) {
    perror("Could not open file!");
    return EXIT_FAILURE;
  }

  // count F
  char ourE = countFre(F);

  // close file
  if (fclose(F) != 0) {
    perror("Failed to close file!");
    return EXIT_FAILURE;
  }

  // get key
  int key = getKey(ourE);

  fprintf(stdout, "%d\n", key);
  return EXIT_SUCCESS;
}

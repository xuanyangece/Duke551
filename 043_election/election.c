#include "election.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me

  // to see whether if it is an empty string
  if (line == NULL) {
    printf("stupid line");
    exit(EXIT_FAILURE);
  }

  // define new variable, initialize it and use it as result
  state_t res;
  res.electoralVotes = 0;
  res.population = 0;
  for (int i = 0; i < 64; i++) {
    res.name[i] = ' ';
  }

  // define a pointer to read string
  const char * p = line;

  // Step1: read name
  res.name[0] = ' ';
  int iOfName = 0;
  while (*p != ':' && *p != '\0') {
    res.name[iOfName++] = *p;
    p++;
  }
  res.name[iOfName] = '\0';

  // if the name is empty
  if (res.name[0] == ' ') {
    printf("stupid line1");
    exit(EXIT_FAILURE);
  }

  // Step2: read population
  p++;
  while (*p <= '9' && *p >= '0') {
    if (!isdigit(*p)) {
      printf("stupid line2");
      exit(EXIT_FAILURE);
    }

    // calculate in decimal
    res.population = res.population * 10 + (*p - '0');
    p++;
  }

  // if population is empty
  if (res.population == 0) {
    printf("stupid line3");
    exit(EXIT_FAILURE);
  }

  // Step3: read vote
  p++;
  while (*p >= '0' && *p <= '9') {
    if (!isdigit(*p)) {
      printf("stupid line4");
      exit(EXIT_FAILURE);
    }

    //calculate in decimal
    res.electoralVotes = res.electoralVotes * 10 + (*p - '0');
    p++;
  }

  return res;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me

  // define result and initialize it
  unsigned int res = 0;

  // count each state and store results in res
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population / 2)
      res += stateData[i].electoralVotes;
  }

  return res;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me

  // define an upper boundary and lower boundary to define the range of recount
  double high = 0.505;
  double low = 0.495;

  // count each state
  for (size_t i = 0; i < nStates; i++) {
    // use cast to convert to double
    double curr = (double)(voteCounts[i]) / (double)(stateData[i].population);

    // judge whether it's in that range
    if (curr <= high && curr >= low) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             curr * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me

  // define max votes and winning state
  double max = 0;
  char * win = NULL;

  // calculate each state
  for (size_t i = 0; i < nStates; i++) {
    double curr = (double)voteCounts[i] / (double)stateData[i].population * 100;
    if (curr > max) {
      max = curr;
      win = stateData[i].name;
    }
  }

  // print result
  printf("Candidate A won %s with %.2f%% of the vote\n", win, max);
}

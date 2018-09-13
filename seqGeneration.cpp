#include <cstdlib>         // For round
#include <cmath>           // For sqrt, log, cos
#include "seqStats.h"      // For GRAMS
#include "seqGeneration.h"

const double PI = 3.14159265358979;

int positiveRandomNormal(int mean, float stdev) {
  float u1, u2, z;
  int norm = 0;
  while (norm <= 0) {
    u1 = randomUniform();
    u2 = randomUniform();
    z = sqrt(-2 * log(u1)) * cos(2*PI*u2);
    norm = round(mean + stdev * z);
  }
  return norm;
}

float randomUniform() {
  return (float)rand()/RAND_MAX;
}

char randomGram(int numA, int numC, int numG, int numT) {
  // Generates a random gram based on the relative occurrences of the grams
  // provided.
  
  int tot = numA + numC + numG + numT;

  // Make sure the total isn't somehow exceeding the maximum limits of rand()
  while (tot > RAND_MAX) {
    numA /= 2;
    numC /= 2;
    numG /= 2;
    numT /= 2;
    tot = numA + numC + numG + numT;
  }

  int roll = rand() % tot;
  if (roll < numA) {
    return 'A';
  } else if (roll < numA + numC) {
    return 'C';
  } else if (roll < numA + numC + numG) {
    return 'G';
  } else {
    return 'T';
  }
  return GRAMS[rand() % 4];
}

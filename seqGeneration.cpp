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

char randomGram() {
  return GRAMS[rand() % 4];
}

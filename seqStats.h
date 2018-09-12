#ifndef _SEQSTATS_H_
#define _SEQSTATS_H_

const int NUM_GRAMS = 4;
const char GRAMS[NUM_GRAMS] = {'A', 'C', 'G', 'T'};

struct stats {
  char* file;
  int seqCount;
  int gramCount;
  int bigramCount;
  float mean;
  float variance;
  float stdev;
};

stats collectStats(char*);
int getLineCount(char*);
int getSum(char*);
float getVariance(char*, float, int);
int getGramCount(char*, char);
int getBigramCount(char*, char, char);
bool bigramMatch(char, char, char, char);
bool gramMatch(char, char);

#endif

#include <fstream>
#include <cmath>
#include "seqStats.h"

using std::ifstream;

stats collectStats(char* fileName) {
  stats s;
  s.file = fileName;

  s.seqCount = getLineCount(fileName);
  s.gramCount = getSum(fileName);
  s.bigramCount = s.gramCount - s.seqCount;

  s.mean = (float)s.gramCount / s.seqCount;
  s.variance = getVariance(fileName, s.mean, s.seqCount);
  s.stdev = sqrt(s.variance);

  return s;
}

int getLineCount(char* fileName) {
  ifstream seqFile (fileName);

  char c;
  int lineTot = 0;
  while (seqFile.get(c)) {
    if (c == '\n') {
      lineTot++;
    }
  }
  seqFile.close();
  return lineTot;
}

int getSum(char* fileName) {
  ifstream seqFile (fileName);

  char c;
  int tot = 0;
  while (seqFile.get(c)) {
    if (c != '\n') {
      tot++;
    }
  }
  seqFile.close();
  return tot;
}

float getVariance(char* fileName, float mean, int lineCount) {
  ifstream seqFile (fileName);
  char c;
  int seqCount;
  float numerator = 0.0;

  while (seqFile.get(c)) {
    seqCount = 0;
    while (c != '\n') {
      seqCount++;
      seqFile.get(c);
    }
    numerator += (seqCount - mean)*(seqCount - mean);
  }

  seqFile.close();
  return numerator/lineCount;
}

int getGramCount(char* fileName, char gram) {
  ifstream seqFile (fileName);
  char c;
  int count = 0;

  while (seqFile.get(c)) {
    if (gramMatch(gram, c)) {
      count++;
    }
  }

  seqFile.close();
  return count;
}

int getBigramCount(char* fileName, char gram1, char gram2) {
  ifstream seqFile (fileName);
  char cur;
  char prev;
  int count = 0;

  while (seqFile.get(cur)) {
    while (cur != '\n') {
      prev = cur;
      seqFile.get(cur);
      if (bigramMatch(gram1, gram2, prev, cur)) {
        count++;
      }
    }
  }

  seqFile.close();
  return count;
}

bool bigramMatch(char gram1, char gram2, char test1, char test2) {
  return ( gramMatch(gram1, test1) and gramMatch(gram2, test2) );
}

bool gramMatch(char upperGram, char test) {
  char lowerGram = (char)tolower(upperGram);
  return (upperGram == test or lowerGram == test);
}

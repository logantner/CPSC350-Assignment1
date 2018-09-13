#include <fstream>
#include <cmath>
#include "seqStats.h"

using std::ifstream;

stats collectStats(char* fileName) {
  // Calculate various basic statistics from the specified file, stored into
  // a newly created stats struct
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
  // Determines the total number of lines (sequences) in the file. Empty
  // intermediate lines are included in the total
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
  // Counts the total number of valid grams within the entire file (both lower
  // and uppercase a, c, g, and t)
  ifstream seqFile (fileName);
  char c;
  int tot = 0;

  while (seqFile.get(c)) {
    if (isGram(c)) {
      tot++;
    }
  }

  seqFile.close();
  return tot;
}

float getVariance(char* fileName, float mean, int lineCount) {
  // Calculates the sample variance by summing the squared difference between
  // sequence lengths and the sample mean
  ifstream seqFile (fileName);
  char c;
  float numerator = 0.0;

  while (seqFile.get(c)) {
    int seqLength = getSeqLength(seqFile, c);
    numerator += (seqLength - mean) * (seqLength - mean);
  }

  seqFile.close();
  return numerator / lineCount;
}

int getSeqLength(std::ifstream& seqFile, char c) {
  // Determines the length of the sequence at the present location of the
  // provided file. Iterates the file forward to the end of the current line.
  int count = 0;
  while (c != '\n') {
    if (isGram(c)) {
      count++;
    }
    seqFile.get(c);
  }
  return count;
}

int getGramCount(char* fileName, char gram) {
  // Counts the number of occurences of the specified gram within the file
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
  // Counts the number of occurrences of a specified bigram within the file
  ifstream seqFile (fileName);
  char cur, prev = '\n'; // initialized to a nonsense character
  int count = 0;

  while (seqFile.get(cur)) {
    if (bigramMatch(gram1, gram2, prev, cur)) {
      count++;
    }
    // Incremenet prev forward one character
    prev = cur;
  }

  seqFile.close();
  return count;
}

bool bigramMatch(char gram1, char gram2, char test1, char test2) {
  // Returns true if the test bigram formed by {test1, test2} is a valid version
  // of the bigram specified by {gram1, gram2}
  return ( gramMatch(gram1, test1) and gramMatch(gram2, test2) );
}

bool gramMatch(char gram, char test) {
  // Returns true if the test character is a valid version of the specified gram
  test = toupper(test);
  return (gram == test);
}

bool isGram(char c) {
  // Returns true if the character is any viable gram
  c = toupper(c);
  return (c == 'A' or c == 'C' or c == 'G' or c == 'T');
}

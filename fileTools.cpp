#include <iostream>
#include <fstream>

#include "fileTools.h"
#include "seqStats.h"
#include "seqGeneration.h"

using std::endl;
using std::ofstream;

bool seqFileExists(char* fileName) {
  std::ifstream seqFile (fileName);
  if ( seqFile.is_open() ) {
    return true;
    seqFile.close();
  }
  return false;
}

ofstream newOutFile(const char* outFileName) {
  ofstream outFile(outFileName);

  outFile << "Logan Gantner" << endl;
  outFile << "ID: 002307470" << endl << endl;

  return outFile;
}

void writeStatsToFile(ofstream& outFile, const stats& s) {
  addSummaryStats(outFile, s);
  addProbabilities(outFile, s);
}

void addSummaryStats(ofstream& outFile, const stats& s) {
  for (int i = 0; i < 80; ++i) {
    outFile << "/";
  }

  outFile << endl << endl << "File: " << s.file << endl << endl;

  outFile << "======================" << endl;
  outFile << "| Summary Statistics |" << endl;
  outFile << "======================" << endl << endl;
  outFile << "Sum:      " << s.gramCount << endl;
  outFile << "Mean:     " << s.mean << endl;
  outFile << "Variance: " << s.variance << endl;
  outFile << "StDev:    " << s.stdev << endl << endl;
}

void addProbabilities(ofstream& outFile, const stats& s) {
  outFile << "===============================" << endl;
  outFile << "| Probabilities (Percentages) |" << endl;
  outFile << "===============================" << endl << endl;

  addGramProbabilities(outFile, s);
  addBigramProbabilities(outFile, s);
}

void addGramProbabilities(ofstream& outFile, const stats& s) {
  float probOfGram;
  char gram;
  for (int i = 0; i < NUM_GRAMS; ++i) {
    gram = GRAMS[i];
    probOfGram = 100.0 * getGramCount(s.file, gram) / s.gramCount;
    outFile << "Probability of " << gram << ": " << probOfGram << endl;
  }
  outFile << endl;
}

void addBigramProbabilities(ofstream& outFile, const stats& s) {
  float probOfBigram;
  char gram1, gram2;
  for (int i = 0; i < NUM_GRAMS; ++i) {
    gram1 = GRAMS[i];
    for (int j = 0; j < NUM_GRAMS; ++j) {
      gram2 = GRAMS[j];
      probOfBigram = 100.0*getBigramCount(s.file, gram1, gram2) / s.bigramCount;
      outFile << "Probability of " << gram1 << gram2 << ": "
              << probOfBigram << endl;
    }
  }
  outFile << endl;
}

void addRandomSequences(ofstream& outFile, const stats& s, int numSequences) {
  writeRandomHead(outFile);
  for (int i=0; i < numSequences; ++i) {
    int length = positiveRandomNormal(s.mean, s.stdev);
    writeRandomSequence(outFile, length);
  }
  outFile << endl;
}

void writeRandomHead(ofstream& outFile) {
  outFile << "================================" << endl;
  outFile << "| Randomly Generated Sequences |" << endl;
  outFile << "================================" << endl << endl;
}

void writeRandomSequence(ofstream& outFile, int length) {
  for (int i = 0; i < length; ++i) {
    outFile << randomGram();
  }
  outFile << endl;
}

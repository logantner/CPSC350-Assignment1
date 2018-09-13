#include <iostream>
#include <fstream>

#include "fileTools.h"
#include "seqStats.h"
#include "seqGeneration.h"

using std::endl;
using std::ofstream;

bool seqFileExists(char* fileName) {
  // Returns true if the provided string exists as a file in the current dir
  std::ifstream seqFile (fileName);
  if ( seqFile.is_open() ) {
    return true;
    seqFile.close();
  }
  return false;
}

ofstream newOutFile(const char* outFileName) {
  // Creates and returns a new ofstream with boilerplate header
  ofstream outFile(outFileName);

  outFile << "Logan Gantner" << endl;
  outFile << "ID: 002307470" << endl << endl;

  return outFile;
}

void writeStatsToFile(ofstream& outFile, const stats& s) {
  // Appends summary and probability statistics to provided (open) file
  addSummaryStats(outFile, s);
  addProbabilities(outFile, s);
}

void addSummaryStats(ofstream& outFile, const stats& s) {

  // Line break for visibility
  for (int i = 0; i < 80; ++i) {
    outFile << "/";
  }
  // Specify the name of the file to be analyzed
  outFile << endl << endl << "File: " << s.file << endl << endl;

  outFile << "======================" << endl;
  outFile << "| Summary Statistics |" << endl;
  outFile << "======================" << endl << endl;
  outFile << "Sum:      " << s.gramCount << endl;
  outFile << "Mean:     " << s.mean << endl;
  outFile << "Variance: " << s.variance << endl;
  outFile << "StDev:    " << s.stdev << endl << endl;
  outFile << "SeqCount: " << s.seqCount << endl << endl;
}

void addProbabilities(ofstream& outFile, const stats& s) {
  outFile << "===============================" << endl;
  outFile << "| Probabilities (Percentages) |" << endl;
  outFile << "===============================" << endl << endl;

  addGramProbabilities(outFile, s);
  addBigramProbabilities(outFile, s);
}

void addGramProbabilities(ofstream& outFile, const stats& s) {
  // Calculate and write each of the four single-gram probabilities
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
  // Calculate and write each of the sixteen bigram probabilities
  float probOfBigram;
  char gram1, gram2;
  for (int i = 0; i < NUM_GRAMS; ++i) {
    gram1 = GRAMS[i];
    for (int j = 0; j < NUM_GRAMS; ++j) {
      // Allow gram2 to vary while holding gram1 fixed
      gram2 = GRAMS[j];
      probOfBigram = 100.0*getBigramCount(s.file, gram1, gram2) / s.bigramCount;
      outFile << "Probability of " << gram1 << gram2 << ": "
              << probOfBigram << endl;
    }
  }
  outFile << endl;
}

void addRandomSequences(ofstream& outFile, const stats& s, int numSequences) {
  // Write a header, followed by numSequences lines of Randomly
  // generated sequences. Lengths of these sequences follow a normal
  // distribution, with mean and variance coming from the provided stats struct
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
  // Write a sequence of randomly generated grams of specified length, followed
  // by a line break.
  for (int i = 0; i < length; ++i) {
    outFile << randomGram();
  }
  outFile << endl;
}

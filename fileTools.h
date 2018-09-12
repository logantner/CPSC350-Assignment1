#ifndef _OUTFILETOOLS_H_
#define _OUTFILETOOLS_H_

#include <fstream>
#include "seqStats.h"

bool seqFileExists(char*);

std::ofstream newOutFile(const char*);
void writeStatsToFile(std::ofstream&, const stats&);
void addSummaryStats(std::ofstream&, const stats&);

void addProbabilities(std::ofstream&, const stats&);
void addGramProbabilities(std::ofstream&, const stats&);
void addBigramProbabilities(std::ofstream&, const stats&);

void addRandomSequences(std::ofstream&, const stats&, int);
void writeRandomHead(std::ofstream&);
void writeRandomSequence(std::ofstream&, int);

#endif

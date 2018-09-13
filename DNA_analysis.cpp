#include <iostream>
#include <fstream>
#include "seqStats.h"
#include "fileTools.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
  // Check for the correct number of command arguments
  if (argc <= 1) {
    cout << ">> User must enter the name of a text file" << endl;
    return 1;
  }

  std::ofstream outFile = newOutFile("LoganGantner.out");
  char* seqFileName = argv[1];
  char response = 'y';

  while (response == 'y') {
    if (seqFileExists(seqFileName)) {
      stats seqStats = collectStats(seqFileName);
      writeStatsToFile(outFile, seqStats);
      addRandomSequences(outFile, seqStats, 1000);
      cout << ">> Statistics and sequences have been recorded." << endl;
    } else {
      cout << ">> The file '" << seqFileName << "' does not exist." << endl;
    }

    cout << ">> Would you like to process another list? ('y' to continue): ";
    std::cin >> response;
    if (response == 'y') {
      cout << ">> Please enter the name of a new file: ";
      std::cin >> seqFileName;
    }
  }
  outFile.close();

  return 0;
}

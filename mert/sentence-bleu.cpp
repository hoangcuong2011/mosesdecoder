#include <iostream>
#include <vector>
#include <string>

#include "BleuScorer.h"

using namespace std;
using namespace MosesTuning;

int main(int argc, char **argv)
{
  if (argc == 1) {
    cerr << "Usage: ./sentence-bleu ref1 [ref2 ...] < candidate > bleu-scores" << endl;
    return 1;
  }
  vector<string> refFiles(argv + 1, argv + argc);

  // TODO all of these are empty for now
  string config;
  string factors;
  string filter;

  BleuScorer scorer(config);
  scorer.setFactors(factors);
  scorer.setFilter(filter);
  scorer.setReferenceFiles(refFiles); // TODO: we don't need to load the whole reference corpus into memory (this can take gigabytes of RAM if done with millions of sentences)

  // Loading sentences and preparing statistics
  string hypothesisLine;
  size_t sid = 0;
  while (getline(std::cin, hypothesisLine)) 
  {
    ScoreStats scoreStats;
    scorer.prepareStats(sid, hypothesisLine, scoreStats);
    vector<float> stats(scoreStats.getArray(), scoreStats.getArray() + scoreStats.size());
    std::cout << smoothedSentenceBleu(stats) << std::endl;
    ++sid;
  }

  return 0;
}

#ifndef PARTI_H
#include "SolverBase.h"
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

class PartI : public SolverBase
{
vector<vector<int>> graph;
vector<vector<int>> coarseGraph;
vector<vector<int>> scc;

map<int, int> finish;
bool isAyclic = true;

public:
    void read(std::string);
    void solve();
    void write(std::string);
};

#define PARTI_H
#endif
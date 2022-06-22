#ifndef PARTII_H
#include "SolverBase.h"
#include <utility>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

class PartII : public SolverBase
{
private:
    int n ,  m;
    string dijkstra_answer;
    string bellman_answer;
    vector< vector< pair<int,int> > > graph_dijkstra;
    vector< tuple<int,int,int> > edges;
public:
    void read(std::string);
    void solve();
    void write(std::string);
    void dijkstra();
    void bellman_ford();
};

#define PARTII_H
#endif
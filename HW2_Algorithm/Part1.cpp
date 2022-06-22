#include "PartI.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
using pii = pair<int,int>;
const int MAXN = 1005;

int n , m;
vector< vector<int> > SCC(MAXN , vector<int>());
stack<int> stk;
int SCCid[MAXN];
int G[MAXN][MAXN]; // 用鄰接矩陣存圖
int new_graph[MAXN][MAXN];
int low[MAXN] , dfn[MAXN] , dft = 0 , nSCC = 0 , out=0;
bool instk[MAXN];
vector< pii > DAG;
vector< tuple<int,int,int> > Edges;

//DFS
void tarjan(int cur){
	dfn[cur] = low[cur] = ++dft; // init value : dfn(cur) , low(cur)
	instk[cur] = true , stk.push(cur); // push cur into stack

	//遍歷鄰接矩陣，往下一個節點DFS
	for(int nxt=0 ; nxt<1000 ; ++nxt){
		if(!G[cur][nxt]) continue;

		//如果遇到還沒走過的點就直接往下走
		if(!dfn[nxt]){
			tarjan(nxt);
			low[cur] = min(low[cur] , low[nxt]);
		}
		//否則就看他是不是你的祖先，且不屬於任何SCC
		else if(instk[nxt] && dfn[nxt] < dfn[cur]){
			low[cur] = min(dfn[nxt] , low[cur]);
		}
	}

	//如果dfn = low 就代表他沒辦法走到更上面了，自成SCC
	if(low[cur] == dfn[cur]){
		for(int x = -1 ; x != cur ; stk.pop()){
			x = stk.top() , instk[x] = false , SCCid[x] = nSCC;
			SCC[nSCC].push_back(x);
		}
		++nSCC;
	}
	//紀錄離開時間，方便等等找topological sort
	DAG.emplace_back(-(++out) , cur);
}

void PartI::read(std::string file) {
	std::cout << "Part I reading..." << std::endl;
	ifstream fin;
	fin.open(file);
	fin >> n >> m;
	for(int i=0 ; i<m ; ++i){
		int a,b,w;
		fin >> a >> b >> w;
		G[a][b] = w;
	}
	fin.close();
}

void PartI::solve() {
	std::cout << "Part I solving..." << std::endl;

	for(int i=0 ; i<n ; ++i){
		if(!dfn[i]){
			tarjan(i);
		}
	}

	if(nSCC == n){
		// cout << "DAG" << endl;
		sort(DAG.begin() , DAG.end());
	}
	else{
		// cout << "not DAG" << endl;

		//Sort SCCs
		for(int i=0 ; i<nSCC ; ++i){
			sort(SCC[i].begin() , SCC[i].end());
		}
		sort(SCC.begin() , SCC.begin()+nSCC);
		for(int i=0 ; i<nSCC ; ++i){
			for(int &x : SCC[i]){
				SCCid[x] = i;
			}
		}
		
		for(int i=0 ; i<n ; ++i){
			for(int j=0 ; j<n ; ++j){
				if(SCCid[ i ] != SCCid[ j ] && G[i][j]){
					new_graph[ SCCid[i] ][ SCCid[j] ]++;
				}
			}
		}

		for(int i=0 ; i<nSCC ; ++i){
			for(int j=0 ; j<nSCC ; ++j){
				if(new_graph[i][j]){
					Edges.emplace_back(i,j,new_graph[i][j]);
				}
			}
		}
	}
}
void PartI::write(std::string file) {
	std::cout << "Part I writing..." << std::endl;
	ofstream fout;
	fout.open(file);
	if(nSCC == n){
		for(auto &[dfout , vertex] : DAG) fout << vertex << ' ';
		fout << '\n';
	}
	else{
		fout << nSCC << ' ' << Edges.size() << '\n';
		for(auto &[u,v,w] : Edges){
			fout << u << ' ' << v << ' ' << w << '\n';
		}
	}
	fout.close();
}
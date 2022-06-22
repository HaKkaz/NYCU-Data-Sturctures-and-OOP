#include "PartII.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

void PartII::read(std::string file) {
	cout << "Part II reading..." << std::endl;
	ifstream fin;
	fin.open(file);
	fin >> n >> m ;
	cout << n << ' ' << m << '\n';
	graph_dijkstra.resize(n+1);
	for(int i=0 ; i<m ; ++i){
		int a,b,w;
		fin >> a >> b >> w;
		cout << a << ' ' << b << ' ' << w << '\n';
		edges.emplace_back(a,b,w);
		if(w < 0) w = -w;
		graph_dijkstra[a].emplace_back(b,w);
	}
	fin.close();
}

void PartII::dijkstra(){
	const int inf = 1e9;
	vector<int> dis(n,inf);
	priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > pq;
	pq.emplace(0,0);
	dis[0] = 0;
	while(pq.size()){
		auto [cur_dis , cur] = pq.top();
		pq.pop();
		if(dis[cur] != cur_dis) continue;
		for(auto &[nxt , nxt_dis] : graph_dijkstra[cur]){
			if(dis[nxt] > cur_dis + nxt_dis){
				dis[nxt] = cur_dis + nxt_dis;
				pq.emplace(dis[nxt] , nxt);
			}
		}
	}
	dijkstra_answer = to_string(dis[n-1]);
}

void PartII::bellman_ford(){
	const int inf = 1e9;
	vector<int> dis(n,inf);
	dis[0] = 0 ;
	for(int i=1 ; i<n ; ++i){
		vector<int> nxt_dis = dis;
		for(auto &[a,b,w] : edges){
			if(dis[b] > dis[a] + w){
				nxt_dis[b] = dis[a] + w;
			}
		}
		dis = nxt_dis;
	}

	bool check = false;
	for(auto &[a,b,w] : edges){
		if(dis[b] > dis[a] + w){
			check = true;
		}
	}

	if(check){
		bellman_answer = "Negative loop detected!";
	}
	else{
		bellman_answer = to_string(dis[n-1]);
	}
}

void PartII::solve() {
	cout << "Part II solving..." << std::endl;
	dijkstra();
	bellman_ford();
}
void PartII::write(std::string file) {
	cout << "Part II writing..." << std::endl;
	ofstream fout;
	fout.open(file);
	fout << dijkstra_answer << endl;
	fout << bellman_answer << endl;
	fout.close();
}
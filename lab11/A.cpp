#pragma GCC optimize("Ofast", "unroll-loops", "fast-math")
#include<bits/stdc++.h>
// #define int long long
using namespace std;
#define fast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define _ <<' '<<
#define ALL(v) v.begin(),v.end()
#define ft first
#define sd second
#define tiii tuple<int,int,int>
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
#define Edge tuple<int,int,int,int>
int fa[200050];
int Find(int x){
	return (x == fa[x] ? x : fa[x] = Find(fa[x]));
}
bool merge(int a , int b){
	a = Find(a) , b = Find(b);
	if(a == b) return false;
	fa[b] = a;
	return true;
}
int main(){
	fast;
	int n , m;
	cin >> n >> m ;
	for(int i=1 ; i<=n ; ++i) fa[i] = i;
	vector< Edge > edges(m);
	int cnt=0;
	for(auto &[w,a,b,id] : edges) cin >> a >> b >> w , id = cnt++;
	sort(ALL(edges));
	vector<Edge> ans;
	for(auto &[w,a,b,id] : edges){
		// cout << a << ' ' << b << ' ' << w << '\n';
		if(merge(a,b)){
			ans.emplace_back(id,a,b,w);
		}
	}
	sort(ALL(ans));
	for(auto [id,a,b,w] : ans){
		cout << a << ' ' << b << ' ' << w << '\n';
	}
}
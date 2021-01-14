#include "bits/stdc++.h"
using namespace std;
#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
mt19937 rng;
int randomInt(int l, int r){ return uniform_int_distribution<int>(l,r)(rng); }
vector<int> randomSequence(int n, int l, int r){
	assert(l <= r);
	vector<int> res;
	for(int i=1; i<=n; ++i) res.push_back(randomInt(l,r));
	shuffle(begin(res),end(res),rng);
	return res;
}
string randomString(int n, char l, char r){
	assert(l <= r);
	int len = r-l+1; string res;
	for(int i=1; i<=n; ++i) res += char(l + randomInt(0,len-1));
	return res;
}
vector<int> randomDistinctSequence(int n, int l, int r){
	assert(l <= r); assert(n <= r-l+1);
	vector<int> res; set<int> s_res;
	for(int i=1; i<=n; ++i){
		int cur = randomInt(l,r);
		while(s_res.count(cur)) cur = randomInt(l,r);
		res.push_back(cur); s_res.insert(cur);
	}
	shuffle(begin(res),end(res),rng);
	return res;
}
vector<pair<int,int>> randomTree(int n){
	assert(n >= 2);	
	vector<pair<int,int>> edges;
    for(int i=2; i<=n; ++i) edges.emplace_back(randomInt(1,i-1), i);    
    vector<int> perm(n + 1); // re-naming vertices
    for(int i = 1; i <= n; ++i) perm[i] = i;
	shuffle(perm.begin() + 1, perm.end(), rng);
    for(auto& e : edges){
		int a = e.first; a = perm[a];
		int b = e.second; b = perm[b];
	}
	return edges;
}

int main(int argc, char** argv){ 
	rng.seed(argc-argc+atoi(argv[1]));
	
}

/**
* Tarjan's algorithm is a O(N) algorithm to find Strongly Connected Components in graphs
*/


// DIRECTED - FIND SCCs
struct Tarjan{
	int n; vector<int> *adj;
	int nbDfs, nbCmp;
	vector<int> dfsIndex, lowest, cmpID;
	vector<bool> inStck; vector<int> stck;
	Tarjan(int _n, vector<int> _adj[]) : n(_n), adj(_adj) {}
	void dfs(int i) {
		dfsIndex[i] = lowest[i] = ++nbDfs;
		stck.emplace_back(i);
		inStck[i] = true;
		for (int j: adj[i]) {
			if (dfsIndex[j] == -1) { dfs(j); lowest[i] = min(lowest[i], lowest[j]); }
			else if (inStck[j]) lowest[i] = min(lowest[i], lowest[j]);
		}
		if (dfsIndex[i] == lowest[i]) {
			++nbCmp;
			for(;;) { int cur = stck.back(); cmpID[cur] = nbCmp; inStck[cur] = false; stck.pop_back(); if (cur == i) break; }
		}
	}
	void findSCCs() {
		nbDfs = 0; nbCmp = 0;
		dfsIndex.assign(n+1, -1); lowest.assign(n+1, 0); cmpID.assign(n+1, 0); inStck.assign(n+1, false); stck.clear();
		for (int i=1; i<=n; ++i) if (dfsIndex[i] == -1) dfs(i);
	}
};


// UNDIRECTED - FIND BRIDGEs
struct Tarjan{
	int n; vector<int> *adj;
	int nbDfs;
	vector<int> dfsIndex, lowest;
	set<pii> bridges;
	Tarjan(int _n, vector<int> _adj[]) : n(_n), adj(_adj) {}
	void dfs(int u, int prv) {
		dfsIndex[u] = lowest[u] = ++nbDfs;
		for(int v: adj[u]) {
			if (dfsIndex[v] == -1) { dfs(v, u); lowest[u] = min(lowest[u], lowest[v]); if(lowest[v] == dfsIndex[v]) bridges.insert(minmax(u,v)); }
			else if(v != prv) lowest[u] = min(lowest[u], lowest[v]);
		}
	}
	void findBridges() {
		nbDfs = 0;
		dfsIndex.assign(n+1, -1); lowest.assign(n+1, 0); bridges.clear();
		for (int i=1; i<=n; ++i) if (dfsIndex[i] == -1) dfs(i, i);
	}
};



// https://gist.github.com/CsengerG/4cd53ef57ddffbff2d0a

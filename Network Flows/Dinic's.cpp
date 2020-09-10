/**
* Dinic's algorithm is one of the fastest if not the fastest
* max-flow finding algorithms
* Using this class you can create a graph by calling Dinic(n)
* then construct your network by calling addEdge(a, b, edge_capacity)
* Finally call maxFlow() which works in O(V*V*E)
*/

template<typename T> struct Dinic {
	struct Edge { int from, to; T cap, flow; };
	vector<vector<int>> adj;
	vector<Edge> e;
	vector<int> level, edgeCount;
	int n, src, sink;
	Dinic(int _n) {
		n = _n+2; src = _n+1; sink = _n+2;
		adj.assign(n+1, vector<int>());
		level.assign(n+1, 0);
		edgeCount.assign(n+1, 0);
		e.clear();
	}
	void addEdge(int a, int b, T cap) {
		adj[a].emplace_back(size(e));
		e.push_back(Edge{ a, b, cap, 0 });
		
		adj[b].emplace_back(size(e));
		e.push_back(Edge{ b, a, 0, 0 });
	}
	bool bfs() {
		fill(all(level), -1);
		queue<int> q;
		q.push(src);
		level[src] = 0;
		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (int i = 0; i < size(adj[cur]); i++) {
				int curID = adj[cur][i];
				int nxt = e[curID].to;
				if (level[nxt] == -1 && e[curID].flow < e[curID].cap) {
					q.push(nxt);
					level[nxt] = level[cur] + 1;
				}
			}
		}
		return (level[sink] != -1);
	}
	T sendFlow(int cur, T curFlow) {
		if (cur == sink || curFlow == 0) return curFlow;
		for (; edgeCount[cur] < size(adj[cur]); ++edgeCount[cur]) {
				int curID = adj[cur][edgeCount[cur]];
				int nxt = e[curID].to;
				if (level[nxt] == level[cur] + 1) {
					int tmpFlow = sendFlow(nxt, min(curFlow, e[curID].cap - e[curID].flow));
					if (tmpFlow > 0) {
						e[curID].flow += tmpFlow;
						e[curID ^ 1].flow -= tmpFlow;
						return tmpFlow;
					}
				}
		}
		return 0;
	}
	T maxFlow() {
		T f = 0;
		while(bfs()) {
			fill(all(edgeCount), 0);
			while (T tmpFlow=sendFlow(src, INFLL)) f += tmpFlow;
		}
		return f;
	}
};
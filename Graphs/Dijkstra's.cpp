/**
* Dijkstra's shortest path algorithm in a graph
* Given a single source node, it computes the shortest path from that node
* to every other node in O(N*log(N))
*/

void dijkst(int _src, int _dist[]){
	for(int i=1; i<=n; ++i) _dist[i] = INFLL;
	_dist[_src] = 0;
	set<pair<int,int>> _sss;
	for(int i=1; i<=n; ++i) _sss.insert({_dist[i], i});
	while(!empty(_sss)){
		int d; int u;
		tie(d, u) = *begin(_sss);
		_sss.erase(begin(_sss));
		for(auto [v, w]: adj[u]) if(_dist[v] > _dist[u] + w){
			_sss.erase({_dist[v], v});
			_dist[v] = _dist[u] + w;
			_sss.insert({_dist[v], v});
		}
	}
}
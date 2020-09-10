struct Graph {
    int n; vector<vector<int>>adj; vector<int> visited,parent,depth,sz;
    Graph(){}
	Graph(int _n){
        n = _n; adj.assign(n+1, vector<int>());
        visited.assign(n+1, 0); parent.assign(n+1, 0); depth.assign(n+1, 0); sz.assign(n+1, 0);
    }
    void addEdge(int u,int v){ adj[u].push_back(v); adj[v].push_back(u); }
	void explore(){for(int i=1; i<=n; ++i) if(!visited[i]) _dfs(i,i,1);}
    void _dfs(int u,int p,int d){
        visited[u]=true; parent[u]=p; depth[u]=d;
        sz[u]=1; for(int v: adj[u]) if(v!=p && !visited[v]) _dfs(v,u,d+1),sz[u]+=sz[v];
    }
};

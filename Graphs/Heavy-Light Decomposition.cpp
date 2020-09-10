/**
* An advanced type of decomposition on trees(like Centroid Decomposition)
* that divides edges into heavy and light in order to answer queries more efficiently
* It can handle computation of sum of edge weights on a path, maximum weight in a path etc..
* Those can be answered with segment trees on top of this decomposition
*/

vector<int> parent, depth, size, heavy, head, pos;
void dfs(int u, int p) {
    parent[u]=p, depth[u]=depth[p]+1, size[u]=1;
    int mxSize = 0;
    for (int v : g[u]) if (v != parent[v]) {
        dfs(v,u);
        size[u] += size[v];
        if (size[v] > mxSize) mxSize = size[v], heavy[u] = v;
    }
}
int decompose(int u, int curHead, int&curPos) {
    head[u] = curHead, pos[u] = ++curPos;
    if (sz(g[u]) != 0) decompose(heavy[u], curHead, curPos);
    for (int v : g[u]) if (v != parent[u] && v != heavy[u]) decompose(v, v, curPos);
}
void init() {
    int n = sz(g);
    parent.resize(n+1,0); depth.resize(n+1,0); size.resize(n+1,0);
    heavy.resize(n+1,0); head.resize(n+1,0); pos.resize(n+1,0);
    dfs(1,1);
    int curPos=0;
    decompose(1,1,curPos);
}

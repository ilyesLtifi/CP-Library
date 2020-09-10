/**
* The Disjoint set data structure(a union–find data structure)
* is a data structure that stores a collection of disjoint sets
* It stores a partition of a set into disjoint subsets
* The operations it provides are: adding new sets, merging sets (replacing them by their union),
* and finding a representative member of a set.
* It is key in Kruskal's Minimum/Maximum Spanning Tree algorithm
* Its complexity(and its fast speed) depends on the Inverse Ackermann function, see wiki for more detail.
*/

struct Dsu {
    vector<int> _leader, _size;
    Dsu(int _n) { _leader.assign(_n+1, 0); _size.assign(_n+1, 0); for(int i=1; i<=_n; ++i) _leader[i]=i, _size[i]=1; }
    int leader(int x) {return (_leader[x]==x) ? x : _leader[x]=leader(_leader[x]);}
    void unite(int x, int y) { x = leader(x); y = leader(y); if(x != y) _leader[y] = x, _size[x] += _size[y]; }
};
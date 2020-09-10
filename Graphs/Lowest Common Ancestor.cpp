/**
* A O(log(N)) algorithm to find the Lowest Common Ancestor of two nodes in a tree
* Given that some O(N*log(N)) preprocessing is done first
* This uses the Sparse Table class
*/

int lca(int x, int y) {
    if (dep[y] > dep[x]) swap(x, y);
    int diff = dep[x] - dep[y];
    for(int jump=parent.lg; jump>=0; --jump) if(diff&(1<<jump)) x = parent.arr[jump][x];
      
	if (x == y) return x;
      
	for(int jump=parent.lg; jump>=0; --jump) if(parent.arr[jump][x] != parent.arr[jump][y]) {
        x = parent.arr[jump][x]; 
		y = parent.arr[jump][y];
    }
    return parent.arr[0][x];
}
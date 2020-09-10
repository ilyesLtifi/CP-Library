/**
* A class that handles Centroid Decomposition in trees
* This is a Divide & Conquer on trees that constructs a new tree called
* the centroid tree.
* It allows handling many types of queries in O(N*log(N))
*/

struct CentroidTree {
      int n; vector<int> nbChild; vector<bool> done;
	  vector<int> *adj;
      CentroidTree(int _n, vector<int> _adj[]) : adj(_adj){
            n = _n; nbChild.assign(n + 1, 0); done.assign(n + 1, false);
      }
      void dfs(int u, int prv) {
            nbChild[u] = 1;
            for (int v: adj[u]) if (v != prv && !done[v]){
				dfs(v, u);
				nbChild[u]+=nbChild[v];
			}
      }
      int getCentroid(int u, int prv, int nb) {
            int heavy = -1;
            for (int v: adj[u]) if (v != prv && !done[v]) {
                if (heavy == -1 || nbChild[v] > nbChild[heavy]) heavy = v;
            }
            if (heavy != -1 && nbChild[heavy] > nb / 2) return getCentroid(heavy, u, nb);
            else return u;
      }
      int decompose(int u) {
            dfs(u, u);
            int centroid = getCentroid(u, u, nbChild[u]);
            done[centroid] = true;

            int ans = 0;
			// compute ans of current centroid tree
            for (int nxt: adj[centroid]) if (!done[nxt]) ans += decompose(nxt);
            return ans;
      }
};
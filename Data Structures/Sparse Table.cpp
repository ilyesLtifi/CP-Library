/**
* Sparse Tables are like Segment Trees in the sense that it can answer sum/min/max queries
* on ranges, also on paths in trees in O(log(N)) per query + O(N*log(N)) preprocessing
* It uses Binary Exponentiation to achieve that
* THE PROBLEM IS that it does not handle updates at all
* So it is used instead of segment trees because it is way simpler and shorter when no updates are required
* It is also used as preprocessing to find LCAs
*/


// SPARSE TABLE ON ARRAY

template<typename T, int n> struct MiniTable{
	T arr[__lg(n)+1][n+1];
	T& base(int x){ return arr[0][x]; }
	void computeAll(){ for(int i=1; i<=lg[n]; ++i) for(int x=1; x+(1<<i)-1<=n; ++x) arr[i][x] = min(arr[i-1][x], arr[i-1][x+(1<<(i-1))]); }
	T get(int x, int y){ int lgLen=lg[y-x+1]; return min(arr[lgLen][x], arr[lgLen][y-(1<<lgLen)+1]); }
};

template<typename T, int n> struct SumTable{
	T arr[__lg(n)+1][n+1];
	T& base(int x){ return arr[0][x]; }
	void computeAll(){ for(int i=1; i<=lg; ++i) for(int x=1; x+(1<<i)-1<=n; ++x) arr[i][x] = arr[i-1][x]+arr[i-1][x+(1<<(i-1))]; }
	T get(int x, int y){ int len=y-x+1; T ans=0; while(len>0){ int i=lg[len]; len-=(1<<i); ans+=arr[i][x]; x+=(1<<i); } return ans; }
};



// PARENT SPARSE TABLE ON TREE

struct ParentTable{
	int arr[LG+1][N+1];
	int& base(int x){ return arr[0][x]; }
	void computeAll(int n){ for(int i=1; i<=lg[n]; ++i) for(int x=1; x<=n; ++x) arr[i][x] = arr[i-1][arr[i-1][x]]; }
	int get(int x, int len){ while(len > 0){ int i=lg[len]; len -= (1<<i); x = arr[i][x]; } return x; }
};


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

template<typename T, int n> struct MaxiTable{
	T arr[__lg(n)+1][n+1];
	T& base(int x){ return arr[0][x]; }
	void computeAll(){ for(int i=1; i<=lg; ++i) for(int x=1; x+(1<<i)-1<=n; ++x) arr[i][x] = max(arr[i-1][x], arr[i-1][x+(1<<(i-1))]); }
	T get(int x, int y){ int lgLen=lg[y-x+1]; return max(arr[lgLen][x], arr[lgLen][y-(1<<lgLen)+1]); }
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


template<int n> struct ParentTable{
	int arr[__lg(n)+1][n+1];
	int& base(int x){ return arr[0][x]; }
	void computeAll(){ for(int i=1; i<=lg[n]; ++i) for(int x=1; x<=n; ++x) if(dep[x] >= (1<<i)) arr[i][x] = arr[i-1][arr[i-1][x]]; }
	int get(int x, int len){ while(len > 0){ int i=lg[len]; len -= (1<<i); x = arr[i][x]; } return x; }
};







// SPARSE TABLE ON TREE
template<typename T> struct TreeTable{
	int n,lg; T neutral; function<T(T, T)> combine; vector<vector<T>> arr;
	TreeTable(){}
	TreeTable(int _n, T _neutral, function<T(T,T)>_combine): n(_n), lg(__lg(_n)), neutral(_neutral), combine(_combine){
		arr.assign(lg[n]+1, vector<T>(n+1, neutral)); 
	}
	T& base(int x){ return arr[0][x]; }
	T get(int x, int len){
		T ans = neutral;
		while(len > 0){ int i = lg[len]; len -= (1<<i); ans = combine(ans, arr[i][x]); x = parent.arr[i][x]; }
		return ans;
	}
	void computeAll(){
		for(int i=1; i<=lg; ++i) for(int x=1; x<=n; ++x) if(dep[x] >= (1<<i)){
			int nxt = parent.arr[i-1][x];
			arr[i][x] = combine(arr[i-1][x], arr[i-1][nxt]);
		}
	}
};
minWeight = TreeTable<int>(10, INF, [&](int old,int cur){return min(old, cur);});







// GENERIC

template<typename T> struct SparseTable{
	int n,lg;
	vector<vector<T>> arr;
	T neutral;
	function<T(T, T)> combine;
	function<int(int, int)> Nxt;
	function<bool(int, int)>  HasNxt;
	SparseTable(){}
	SparseTable(int _n, T _neutral, function<T(T,T)>_combine,function<int(int,int)>_nxt,function<int(int,int)> _hasNxt){
		n = _n;
		lg = __lg(_n);
		neutral = _neutral;
		arr.assign(lg[n]+1, vector<T>(n+1, neutral));
		combine = _combine;
		Nxt = _nxt;
		HasNxt = _hasNxt;
	}
	T& base(int x){
		return arr[0][x];
	}
	T get(int x, int len){
		T ans = neutral;
		while(len > 0){
			int i = lg[len];
			len -= (1<<i);
			ans = combine(ans, arr[i][x]);
			x = Nxt(x, i);
		}
		return ans;
	}
	void computeAll(){
		for(int i=1; i<=lg; ++i) for(int x=1; x<=n; ++x) if(HasNxt(x,i)){
			int nxt = Nxt(x, i-1);
			arr[i][x] = combine(arr[i-1][x], arr[i-1][nxt]);
		}
	}
};


// sparse tables on trees
parent = SparseTable<int>(n,0,
[&](int old,int cur){return cur;},
[&](int x,int i){return parent.arr[i][x];},
[&](int x,int i){return dep[x] >= (1<<i);});

minWeight = SparseTable<int>(n,INF,
[&](int old,int cur){return min(old,cur);},
[&](int x,int i){return parent.arr[i][x];},
[&](int x,int i){return dep[x] >= (1<<i);});

// sparse tables on arrays
mini = SparseTable<int>(n,INF,
[&](int old,int cur){return min(old,cur);},
[&](int x,int i){return x+(1<<i);},
[&](int x,int i){return x+(1<<i)-1 <= mini.n;});

sum = SparseTable<int>(n,0,
[&](int old,int cur){return old + cur;},
[&](int x,int i){return x+(1<<i);},
[&](int x,int i){return x+(1<<i)-1 <= sum.n;});

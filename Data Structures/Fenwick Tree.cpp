/**
* This is a data structure that can efficiently update elements and
* calculate prefix sums in a table of numbers
* This allows the handling of many types of queries in O(log(N)):
* 		add V to the i_th element
* 		return the sum of [l; r] interval in the array
*/

struct Fenwick {
	int n = N, _offset; int arr[N+1];
	Fenwick(int offset=0){ _offset = offset; }
	void updateAdd(int qI, int qVal) { qI+=_offset; while(qI <= n){ arr[qI] += qVal; qI += (qI & -qI); } }
	int querySum(int qI) { int ans = 0; while(qI > 0){ ans += arr[qI]; qI -= (qI & -qI); } return ans; }
	int querySum(int qL, int qR){ qL+=_offset, qR+=_offset; return (qL <= qR) ? querySum(qR) - querySum(qL-1) : 0; }
};


template<typename T, int _N, int _offset = 0> struct Fenwick {
	int n = _N; T arr[_N+1];
	void updateAdd(int qI, T qVal) { qI+=_offset; while(qI <= n){ arr[qI] += qVal; qI += (qI & -qI); } }
	T querySum(int qI) { T ans = 0; while(qI > 0){ ans += arr[qI]; qI -= (qI & -qI); } return ans; }
	T querySum(int qL, int qR){ qL+=_offset, qR+=_offset; return (qL <= qR) ? querySum(qR) - querySum(qL-1) : 0; }
};




template<int _N, int _offset = 0> struct OrderedFenwick {
	int n = _N; OrderedSet<int> arr[_N+1];
	void updateAdd(int qI, int qVal) { qI+=_offset; while(qI <= n){ arr[qI].insert(qVal); qI += (qI & -qI); } }
	void updateRmv(int qI, int qVal) { qI+=_offset; while(qI <= n){ arr[qI].erase(qVal); qI += (qI & -qI); } }
	int queryNb(int qI, int lo, int hi) { int ans = 0; while(qI > 0){ ans += arr[qI].order_of_key(hi+1) - arr[qI].order_of_key(lo); qI -= (qI & -qI); } return ans; }
	int queryNb(int qL, int qR, int lo, int hi){ qL+=_offset, qR+=_offset; return (qL <= qR) ? queryNb(qR, lo, hi) - queryNb(qL-1, lo, hi) : 0; }
};





int getSum(int BITx[], int index){
	int sum = 0;
	index = index + 1;
	while (index > 0) {
		sum += BITx[index];
		index -= index & (-index);
	}
	return sum;
}
void updateBIT(int BITx[], int n, int index, int val) {
	index = index + 1;
	while (index <= n) {
		BITx[index] += val;
		index += index & (-index);
	}
}

int sum(int x) { return (getSum(x) * x) - getSum(x); }

void updateRange(int n, int val, int l, int r) {
	updateBIT(BIT1,n,l,val);
	updateBIT(BIT1,n,r + 1,-val);

	updateBIT(BIT2,n,l,val * (l - 1));
	updateBIT(BIT2,n,r + 1,-val * r);
}

int rangeSum(int l, int r){ return sum(r, BIT1, BIT2) - sum(l - 1, BIT1, BIT2); }

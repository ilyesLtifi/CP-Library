/**
* A Data Structure that allows operations on ranges
* Min/Max/Sum/Gcd/other functions on ranges + single/range updates in O(log(N)) per query + O(N*log(N)) preprocessing at the start
* Can be used along Heavy-Light Decomposition to achieve these queries on paths in trees just like regular array ranges
* Can also be used with Lazy Propagation, which allows range updates like: add +X to a range and sum/min/max/others on it
*/

struct SegmentTree{
	// #define int long long
	int n, sum[4*N], lazy[4*N];
    SegmentTree(int nn){ n = 1<<(__lg(nn-1)+1); }
	
    void pushDown(int i, int st, int en){
        sum[i] += lazy[i] * (en-st+1);
        if(st != en){
            lazy[2*i] += lazy[i];
            lazy[2*i+1] += lazy[i];
        }
        lazy[i] = 0;
    }

    void pushUp(int i, int st, int en){
        sum[i] = sum[2*i] + sum[2*i+1];
    }

    int Sum(int qL, int qR){ return Sum(qL, qR, 1, 1, n); }
	int Sum(int qL, int qR, int i, int st, int en) {
        if(lazy[i]) pushDown(i, st, en);
		if (en < qL || qR < st) return 0;
        if (qL <= st && en <= qR) return sum[i];
 
		int mid = (st + en)/2;
		int l = Sum(qL, qR, 2*i, st, mid);
		int r = Sum(qL, qR, 2*i+1, mid+1, en); 
		return l + r;
	}
	
    void Add(int qL, int qR, int qVal){ Add(qL, qR, qVal, 1, 1, n); }
	void Add(int qL, int qR, int qVal, int i, int st, int en) {
        if(lazy[i]) pushDown(i, st, en);
        if (en < qL || qR < st) return;
        if (qL <= st && en <= qR){
            lazy[i] += qVal;
            pushDown(i, st, en);
            return;
        }
 
		int mid = (st + en)/2;
		Add(qL, qR, qVal, 2*i, st, mid);
		Add(qL, qR, qVal, 2*i+1, mid+1, en);

        pushUp(i, st, en);
	}
};

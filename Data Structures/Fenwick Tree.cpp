/**
* This is a data structure that can efficiently update elements and
* calculate prefix sums in a table of numbers
* This allows the handling of many types of queries in O(log(N)):
* 		add V to the i_th element
* 		return the sum of [l; r] interval in the array
*/

struct Fenwick {
	// #define int long long
	int n; int arr[SIZE+2];
	Fenwick(){}
	Fenwick(int _n){ n=_n; memset(arr, 0, sizeof(arr)); }
	void add(int qI, int qVal) { while(qI <= n){ arr[qI] += qVal; qI += (qI & -qI); } }
	int sum(int qI) { int ans = 0; while(qI > 0){ ans += arr[qI]; qI -= (qI & -qI); } return ans; }
	int sum(int qL, int qR){ return (qL <= qR) ? querySum(qR) - querySum(qL-1) : 0; }
};

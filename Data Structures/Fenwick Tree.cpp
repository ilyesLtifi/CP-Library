/**
* This is a data structure that can efficiently update elements and
* calculate prefix sums in a table of numbers
* This allows the handling of many types of queries in O(log(N)):
* 		add V to the i_th element
* 		return the sum of [l; r] interval in the array
*/


template<typename T> struct Fenwick {
    int n; T arr[N+2];
    Fenwick(int _n){ n=_n; }
    void clear(){ memset(arr, 0, sizeof(arr)); }
    void Add(int qI, T qVal) { while(qI <= n){ arr[qI] += qVal; qI += (qI & -qI); } }
    T Sum(int qI) { T ans = 0; while(qI > 0){ ans += arr[qI]; qI -= (qI & -qI); } return ans; }
    T Sum(int qL, int qR){ return (qL <= qR) ? Sum(qR) - Sum(qL-1) : 0; }
};

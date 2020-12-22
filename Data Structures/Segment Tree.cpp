/**
* A Data Structure that allows operations on ranges
* Min/Max/Sum/Gcd/other functions on ranges + single/range updates in O(log(N)) per query + O(N*log(N)) preprocessing at the start
* Can be used along Heavy-Light Decomposition to achieve these queries on paths in trees just like regular array ranges
* Can also be used with Lazy Propagation, which allows range updates like: add +X to a range and sum/min/max/others on it
*/


TOO LAZY TO PUSH TO MY CHILDREN
NOT TOO LAZY TO PUSH TO MYSELF

struct Node{ LL mini = 0, lazy = 0; LL valueMini(){ return mini+lazy; } };
struct SegmentTree{
	int n; vector<Node> tree;
    SegmentTree(int size){ n = (1<<(int)ceil(log2(size))); tree.assign(2*n, Node()); }
	LL queryMini(const int& qL, const int& qR){ return queryMini(qL, qR, 1, 1, n); }
	LL queryMini(const int& qL, const int& qR, int i, int st, int en) {
		if (en < qL || qR < st) return INFLL;
		if (qL <= st && en <= qR) return tree[i].valueMini();

		tree[2*i].lazy += tree[i].lazy;
		tree[2*i+1].lazy += tree[i].lazy;
		tree[i].lazy = 0;
 
		int mid = (st + en) / 2;
		LL l = queryMini(qL, qR, 2*i, st, mid);
		LL r = queryMini(qL, qR, 2*i+1, mid+1, en);
 
		tree[i].mini = min(tree[2*i].valueMini(), tree[2*i+1].valueMini());
 
		return min(l, r);
	}
	inline void updateAdd(const int& qL, const int& qR, const LL& qVal){ updateAdd(qL, qR, qVal, 1, 1, n); }
	inline void updateAdd(const int& qL, const int& qR, const LL& qVal, int i, int st, int en) {
        if (en < qL || qR < st) return;
		if (qL <= st && en <= qR) { tree[i].lazy += qVal; return; }
		
		tree[2*i].lazy += tree[i].lazy;
		tree[2*i+1].lazy += tree[i].lazy;
		tree[i].lazy = 0;
 
		int mid = (st + en) / 2;
		updateAdd(qL, qR, qVal, 2*i, st, mid);
		updateAdd(qL, qR, qVal, 2*i+1, mid+1, en);
 
		tree[i].mini = min(tree[2*i].valueMini(), tree[2*i+1].valueMini());
	}
};
SegmentTree segt(N);


-------------------


template<typename T> struct Node{ T mini = INF; };                   // CHANGE HERE
template<typename T, int _n> struct SegmentTree{
	int n = (1<<(int)ceil(log2(_n))); Node<T> tree[2*n];
	T queryMini(const int& qL, const int& qR){ return _queryMini(qL, qR, 1, 1, n); }
	T _queryMini(const int& qL, const int& qR, int i, int st, int en){
		if (en < qL || qR < st) return INF;
		if (qL <= st && en <= qR) return tree[i].mini;
		int mid = (st + en) / 2;
		T _left = _queryMini(qL, qR, i*2, st, mid);
		T _right = _queryMini(qL, qR, i*2+1, mid+1, en);
		return min(_left, _right);
	}
	void updateInd(const int& qInd, const T& qVal) {
		int i = qInd + n-1;
		tree[i].mini = qVal;
		while(i/2 >= 1){
			i /= 2;
			tree[i].mini = min(tree[i*2].mini, tree[i*2+1].mini);
		}
	}
};


-------------------


enum Query{Mini, Maxi, Sum}; enum Update{Add};
#define T int
struct Node{
	int st, en;
	T mini=0;
	T maxi=0;
	T sum=0;
	T lazy=0;
	Node(){}
	inline void pushToChildren(Node &l, Node &r);
	inline T value(const Query &Q);
	inline void updateFromChildren(Node &l, Node &r);
};
inline T neutral(const Query &Q){
	if(Q == Mini) return INF;
	else if(Q == Maxi) return -INF;
	else if(Q == Sum) return 0;
	else assert(false);
}
inline T combine(const Query &Q, const T &l, const T &r){
	if(Q == Mini) return min(l, r);
	else if(Q == Maxi) return max(l, r);
	else if(Q == Sum) return l + r;
	else assert(false);
}
inline void apply(const Update &U, Node&x, const T &qVal){
	if(U == Add) x.lazy += qVal;
	else assert(false);
}
inline T Node::value(const Query &Q){
	if(Q == Mini) return mini + lazy;
	else if(Q == Maxi) return maxi + lazy;
	else if(Q == Sum) return sum + lazy*(en-st+1);
	else assert(false);
}
inline void Node::pushToChildren(Node &l, Node &r){
	l.lazy += lazy;
	r.lazy += lazy;
	lazy = 0;
}
inline void Node::updateFromChildren(Node &l, Node &r){
	mini = combine(Mini, l.value(Mini) , r.value(Mini));
	maxi = combine(Maxi, l.value(Maxi) , r.value(Maxi));
	sum = combine(Sum, l.value(Sum) , r.value(Sum));
}
struct SegmentTree {
	int n; vector<Node> tree;
	SegmentTree(int _n) { n = (1<<(int)ceil(log2(_n))); tree.assign(n<<1, Node()); build(1,1,n); }
	inline void build(int i, int _st, int _en) {
		tree[i].st = _st; tree[i].en = _en;
		if (_st == _en) return;
		int mid = (_st + _en) >> 1;
		build((i<<1),      _st,    mid);
		build((i<<1)|1,  mid+1, _en);
	}
	inline T query(const Query& Q, const int& qL, const int& qR, int i = 1) {
		if (tree[i].en < qL || qR < tree[i].st) return neutral(Q);
		if (qL <= tree[i].st && tree[i].en <= qR) return tree[i].value(Q);
		tree[i].pushToChildren(tree[(i<<1)], tree[(i<<1)|1]);
		T l = query(Q, qL, qR, (i<<1));
		T r = query(Q, qL, qR, (i<<1)|1);
		tree[i].updateFromChildren(tree[(i<<1)], tree[(i<<1)|1]);
		return combine(Q, l, r);
	}
	inline void update(const Update &U, const int& qL, const int& qR, const T& qVal, int i = 1) {
		if (tree[i].en < qL || qR < tree[i].st) return;
		if (qL <= tree[i].st && tree[i].en <= qR) { apply(U, tree[i], qVal); return; }
		tree[i].pushToChildren(tree[(i<<1)], tree[(i<<1)|1]);
		update(U, qL, qR, qVal, (i<<1));
		update(U, qL, qR, qVal, (i<<1)|1);
		tree[i].updateFromChildren(tree[(i<<1)], tree[(i<<1)|1]);
	}
};


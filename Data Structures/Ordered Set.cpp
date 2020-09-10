/**
* An Ordered Set is just what is sounds like.
* A regular C++ Set<> plus 2 functions that add elements ordering (explained below)
* It is reasonably fast and I always use it when I can instead of segment trees
* because they are short and they most likely do the job
* I also created another class to mimic ordering for C++ Multiset<> that supports duplicate elements
*/


// K-th LARGEST         (0-indexed)    *s.find_by_order(K) 
// NUMBER OF ELEMENTS < X              s.order_of_key(X)
// NUMBER OF ELEMENTS IN RANGE [L;R]   s.order_of_key(r+1) - s.order_of_key(l)


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T> using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T> struct OrderedMultiset{
	tree<pair<T,int>, null_type, less<pair<T,int>>, rb_tree_tag, tree_order_statistics_node_update> _s;
	int id = 1;
	void insert(const T &x){ _s.insert({x, id}); ++id; }
	void erase(const T &x){ auto it=_s.upper_bound({x, -1}); if(it!=_s.end() && it->first==x) _s.erase(it); }
	int count(const T &x){ return _s.order_of_key({x, 1e9}) - _s.order_of_key({x, -1}); }
	int count(const T &l, const T &r){ return _s.order_of_key({r, 1e9}) - _s.order_of_key({l, -1}); }  // [l;r] inclusive
	T operator[](const int& ind){ assert(1 <= ind && ind <= size(_s)); return _s.find_by_order(ind-1)->first; } // 1-indexed
};
/**
* A simple implementation of the O(N*log(N)) Longest Increasing(non-decreasing) Subsequence algorithm
*/

set<int> lis; // multiset if there are duplicates
for(int i=1; i<=n; ++i) {
	auto it = lis.upper_bound(X);  // lower_bound for strictly increasing
	if (it != end(lis)) lis.erase(it);
	lis.insert(X);
}

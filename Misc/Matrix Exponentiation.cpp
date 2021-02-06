/**
* This is a technique that uses matrices in order to solve linear recurrence equations
* like the n-th fibonacci number in O(log(N)) - so it can be done for extremly big N
* This is using the Binary Exponentiation Power algorithm but on matrices, to find M²
* for example when M is a matrix
*/

namespace MatrixExp{
	#define matrix vector<vector<long>>
	matrix mul(const matrix& a, const matrix& b){
		int n1 = size(a); int m1 = size(a[0]);
		int n2 = size(b); int m2 = size(b[0]);
		assert(m1 == n2);
		int shared = m1;
		matrix res(n1, vector<long>(m2, 0));
		for(int i=1; i<=n1; ++i) for(int j=1; j<=m2; ++j){
			for(int mid=1; mid<=shared; ++mid) res[i-1][j-1] = add(res[i-1][j-1], mul(a[i-1][mid-1],b[mid-1][j-1]));
		}
		return res;
	}
	matrix power(const matrix& x, const long& n){
		matrix y(size(x), vector<long>(size(x[0]), 0));
		for(int i=1; i<=size(y); ++i) y[i-1][i-1]=1;
		if(n == 0) return y;
		y=power(x, n>>1); y=mul(y,y);
		return (n&1) ? mul(y,x) : y;
	}
} using namespace MatrixExp;

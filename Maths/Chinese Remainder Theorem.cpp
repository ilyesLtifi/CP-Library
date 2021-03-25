/**
* Advanced and not very widely used algorithm, but it does appear with other algorithms.
* Helps with solving some forms of modular systems of equations. Read more here: https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
* Coupled with diophantine equations solvers because it uses it.
*/

namespace CRT{
	#define T int
	
	T _dioph(T a, T b, T& x, T& y) { if(b > 0){ T g=_dioph(b,a%b,y,x); y-=(a/b)*x; return g; } x=1, y=0; return a; }
	bool dioph(T a, T b, T c, T& x, T& y){ T g=gcd(a,b); if(c%g!=0) return false; _dioph(a, b, x, y); x*=c/g; y*=c/g; return true; }

	T CRT(T a, T n, T b, T m){
		T x, y;
		assert(dioph(n, m, b-a, x, y));
		T mod = lcm(n, m);
		T res = ((T)x*n + a) % mod;
		if(res < 0) res = (res + (T)mod*(abs(res)/mod + 1)) % mod;
		return res;
	}

	T CRT(const vector<T>& rems, const vector<T>& mods){
		T rem = rems.front(), mod = mods.front();
		for(int i=1; i<=size(rems)-1; ++i){
			rem = CRT(rem, mod, rems[i], mods[i]);
			mod = lcm(mod, mods[i]);
		}
		return rem;
	}

};
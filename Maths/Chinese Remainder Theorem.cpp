/**
* Advanced and not very widely used algorithm, but it does appear with other algorithms.
* Helps with solving some forms of modular systems of equations. Read more here: https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
* Coupled with diophantine equations solvers because it uses it.
*/

long _dioph(long a, long b, long& x, long& y) { if(b > 0){ long g=_dioph(b,a%b,y,x); y-=(a/b)*x; return g; } x=1, y=0; return a; }
bool dioph(long a, long b, long c, long& x, long& y){ long g=gcd(a,b); if(c%g!=0) return false; _dioph(a, b, x, y); x*=c/g; y*=c/g; return true; }

long CRT(long a, long n, long b, long m){
	long x, y;
	assert(dioph(n, m, b-a, x, y));
	long mod = lcm(n, m);
	long res = ((long)x*n + a) % mod;
	if(res < 0) res = (res + (long)mod*(abs(res)/mod + 1)) % mod;
	return res;
}

long CRT(const vector<long>& rems, const vector<long>& mods){
	long rem = rems.front(), mod = mods.front();
	for(int i=1; i<=size(rems)-1; ++i){
		rem = CRT(rem, mod, rems[i], mods[i]);
		mod = lcm(mod, mods[i]);
	}
	return rem;
}


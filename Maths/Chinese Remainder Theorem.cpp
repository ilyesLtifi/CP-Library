/**
* Advanced and not very widely used algorithm, but it does appear with other algorithms.
* Helps with solving some forms of modular systems of equations. Read more here: https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
* Coupled with diophantine equations solvers because it uses it.
*/

LL _dioph(LL a, LL b, LL& x, LL& y) { if(b > 0){ LL g=_dioph(b,a%b,y,x); y-=(a/b)*x; return g; } x=1, y=0; return a; }
bool dioph(LL a, LL b, LL c, LL& x, LL& y){ LL g=gcd(a,b); if(c%g!=0) return false; _dioph(a, b, x, y); x*=c/g; y*=c/g; return true; }

LL CRT(LL a, LL n, LL b, LL m){
	LL x, y;
	assert(dioph(n, m, b-a, x, y));
	LL mod = lcm(n, m);
	LL res = ((LL)x*n + a) % mod;
	if(res < 0) res = (res + (LL)mod*(abs(res)/mod + 1)) % mod;
	return res;
}

LL CRT(const vector<LL>& rems, const vector<LL>& mods){
	LL rem = rems.front(), mod = mods.front();
	for(int i=1; i<=size(rems)-1; ++i){
		rem = CRT(rem, mod, rems[i], mods[i]);
		mod = lcm(mod, mods[i]);
	}
	return rem;
}


/**
* Some Math Helper functions that compute modulo addition, multiplication, inverse etc..
*/

LL MOD = 0;
inline LL mul(const LL& x, const LL& y, const LL& mod = MOD) { return (x*y)%mod; }
inline LL add(const LL& x, const LL& y, const LL& mod = MOD) { LL z=x+y; return (z>=mod+mod)?z%mod:((z>=mod)?z-mod:((z<0)?z+mod:z)); }
inline LL power(const LL& x, const LL& n, const LL& mod = MOD){if(n==0)return 1;LL y=power(x, n>>1, mod);y=mul(y,y,mod);return (n&1)?mul(y,x,mod):y;}
inline LL _power(const LL& x, const LL& n){if(n==0)return 1;LL y=_power(x, n>>1);y=y*y;return (n&1)?y*x:y;}

LL _fact[SIZE+2] = {0}; inline LL fact(const LL& x){ return (x==0 ? 1 : (_fact[x]!=0 ? _fact[x] : _fact[x]=mul(x, fact(x-1)))); }

LL _invfact[SIZE+2] = {0}; inline LL invfact(const LL& x){ return (x==0 ? 1 : (_invfact[x]!=0 ? _invfact[x] : _invfact[x]=power(fact(x), MOD-2))); }

inline LL inv(const LL& x, const LL& mod = MOD){ return power(x, mod-2, mod); }
OR
LL _inv[SIZE+2] = {0}; inline LL inv(const LL& x){ return (x==0 ? 1 : (_inv[x]!=0 ? _inv[x] : _inv[x]=power(x, MOD-2))); }

inline LL cnk(const LL& n, const LL& k){ return (n<k)?0:mul(fact(n),inv(mul(fact(k),fact(n-k)))); }
OR
LL _cnk[SIZE+2][SIZE+2] = {0}; inline LL cnk(const LL& n, const LL& k){ return (n<k)?0:(k==0)?1:(_cnk[n][k]!=0?_cnk[n][k]:_cnk[n][k]=add(cnk(n-1,k),cnk(n-1,k-1))); }




for(int i=1; i<=X; ++i) spf[i] = i;
for(int i=2; i<=X; ++i) if(spf[i] == i) for(int j=i+i; j<=X; j+=i) spf[j] = min(spf[j], i);

phi[1] = 1;
for(int i=2; i<=X; i++) phi[i] = (spf[i] == spf[i/spf[i]]) ? phi[i/spf[i]]*spf[i] : phi[i/spf[i]]*(spf[i]-1);




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

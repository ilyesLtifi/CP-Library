/**
* Some Math Helper functions that compute modulo addition, multiplication, inverse etc..
*/

inline LL add(const LL& x, const LL& y) { LL z=x+y; return (z>=MOD+MOD)?z%MOD:((z>=MOD)?z-MOD:((z<0)?z+MOD:z)); }
inline LL mul(const LL& x, const LL& y) { return (x*y)%MOD; }
inline LL power(const LL& x, const LL& n){if(n==0)return 1;LL y=power(x, n>>1);y=mul(y,y);return (n&1)?mul(y,x):y;}
inline LL _power(const LL& x, const LL& n){if(n==0)return 1;LL y=_power(x, n>>1);y=y*y;return (n&1)?y*x:y;}
LL _fact[SIZE+2] = {0}; inline LL fact(const LL& x){ return (x==0 ? 1 : (_fact[x]!=0 ? _fact[x] : _fact[x]=mul(x, fact(x-1)))); }
LL _invfact[SIZE+2] = {0}; inline LL invfact(const LL& x){ return (x==0 ? 1 : (_invfact[x]!=0 ? _invfact[x] : _invfact[x]=power(fact(x), MOD-2))); }
inline LL inv(const LL& x){ return power(x, MOD-2); }
inline LL cnk(const LL& n, const LL& k){ return (n<k)?0:mul(fact(n),inv(mul(fact(k),fact(n-k)))); }


LL _inv[SIZE+2] = {0}; inline LL inv(const LL& x){ return (x==0 ? 1 : (_inv[x]!=0 ? _inv[x] : _inv[x]=power(x, MOD-2))); }

LL _cnk[SIZE+2][SIZE+2] = {0}; inline LL cnk(const LL& n, const LL& k){ return (n<k)?0:(k==0)?1:(_cnk[n][k]!=0?_cnk[n][k]:_cnk[n][k]=add(cnk(n-1,k),cnk(n-1,k-1))); }

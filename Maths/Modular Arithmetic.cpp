/**
* Some Math Helper functions that compute addition, multiplication, inverse etc.. modulo a prime number.
*/

long long add(long long x, long long y) { long long z=x+y; while(z>=MOD)z-=MOD; return z; }
long long add(const initializer_list<long long>& l){ long long x=0; for(long long y: l) x=add(x,y); return x; }
long long mul(long long x, long long y) { long long z=x*y; return (z>=MOD)?z%MOD:z; }
long long mul(const initializer_list<long long>& l){ long long x=1; for(long long y: l) x=mul(x,y); return x; }
long long power(long long x, long long n){if(n==0)return 1;long long y=power(x,n>>1);y=mul(y,y);return (n&1)?mul(y,x):y;}
long long inv(long long x){ return power(x,MOD-2); }
long long _inv[SIZE+2] = {0}; long long inv(long long x){ return (x==0 ? 1 : (_inv[x]!=0 ? _inv[x] : _inv[x]=power(x, MOD-2))); }
long long _fact[SIZE+2] = {0}; long long fact(long long x){ return (x==0?1:(_fact[x]!=0?_fact[x]:_fact[x]=mul(x,fact(x-1)))); }
long long _invfact[SIZE+2] = {0}; long long invfact(long long x){ return (x==0 ? 1 : (_invfact[x]!=0 ? _invfact[x] : _invfact[x]=power(fact(x), MOD-2))); }
long long cnk(long long n, long long k){ return (n<k)?0:mul(fact(n),inv(mul(fact(k),fact(n-k)))); }
long long _cnk[SIZE+2][SIZE+2] = {0}; long long cnk(long long n, long long k){ return (n<k)?0:(k==0)?1:(_cnk[n][k]!=0?_cnk[n][k]:_cnk[n][k]=add(cnk(n-1,k),cnk(n-1,k-1))); }


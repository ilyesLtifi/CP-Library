namespace MillerRabin{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    inline LL power(const LL& x, const LL& n, const LL& mod = MOD){if(n==0)return 1;LL y=power(x, n>>1, mod);y=mul(y,y,mod);return (n&1)?mul(y,x,mod):y;}
    
    bool millerTest(LL d, LL n) { 
        LL a = uniform_int_distribution<int>(2, n-2)(rng);
    
        LL x = power(a, d, n); 
    
        if (x == 1  || x == n-1) 
        return true; 
    
        while (d != n-1){ 
            x = (x * x) % n; 
            d *= 2; 
    
            if (x == 1) return false; 
            if (x == n-1) return true; 
        } 
    
        return false; 
    } 
    
    bool isPrime(LL n, int k) { 
        if (n <= 1 || n == 4)  return false; 
        if (n <= 3) return true; 
    
        LL d = n - 1; 
        while(d % 2 == 0) d /= 2; 
    
        for(int i = 1; i <= k; i++) if (!millerTest(d, n)) return false; 
    
        return true; 
    } 
} using namespace MillerRabin;

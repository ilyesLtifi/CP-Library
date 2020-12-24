/**
 * Taken from github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/Factor.h
*/

namespace PollardRho{
    LL pollardRho(LL n) {
        auto f = [n](LL x) { return mul(x, x, n) + 1; };
        LL x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 || gcd(prd, n) == 1) {
            if (x == y) x = ++i, y = f(x);
            if ((q = mul(prd, max(x,y) - min(x,y), n))) prd = q;
            x = f(x), y = f(f(y));
        }
        return gcd(prd, n);
    }
    vector<LL> primeFactors(LL n) {
        if(n == 1) return {};
        if(isPrime(n)) return {n};
        LL x = pollardRho(n);
        auto l = primeFactors(x), r = primeFactors(n / x);
        l.insert(l.end(), all(r));
        return l;
    }
} using namespace PollardRho;
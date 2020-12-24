/**
 * Taken from github.com/kth-competitive-programming/kactl/blob/master/content/number-theory/MillerRabin.h
*/

namespace MillerRabin{
    bool isPrime(LL n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        LL A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        LL s = __builtin_ctzll(n-1);
        LL d = n >> s;
        for (LL a : A) {   // ^ count trailing zeroes
            LL p = power(a%n, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--)
                p = mul(p, p, n);
            if (p != n-1 && i != s) return 0;
        }
        return 1;
    } 
} using namespace MillerRabin;

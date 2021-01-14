/**
* Computes all prime numbers <= X in O(X)
* In this implementation I'm using to compute something more; spf[i] is the smallest-prime-factor of i.
* 
* The phi-function(Euler's totient function) is also computed using the sieve. Read about it here: cp-algorithms.com/algebra/phi-function.html
*/

int primeCnt = 0;
for(int i=2; i<=X; ++i) spf[i] = 0;
for(int i=2; i<=X; ++i) {
    if(!spf[i]) primes[++primeCnt] = i, spf[i] = i;
    for(int j=1; j<=primeCnt && 1LL*i*primes[j]<X && primes[j]<=spf[i]; j++) spf[i*primes[j]] = primes[j];
}

phi[1] = 1;
for(int i=2; i<=X; i++) phi[i] = (spf[i] == spf[i/spf[i]]) ? phi[i/spf[i]]*spf[i] : phi[i/spf[i]]*(spf[i]-1);

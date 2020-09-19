/**
* Computes all prime numbers <= X in O(X*log(log(X))
* In this implementation I'm using to compute something more; spf[i] is the smallest-prime-factor of i.
* 
* The phi-function(Euler's totient function) is also computed using the sieve. Read about it here: cp-algorithms.com/algebra/phi-function.html
*/

for(int i=1; i<=X; ++i) spf[i] = i;
for(int i=2; i<=X; ++i) if(spf[i] == i) for(int j=i+i; j<=X; j+=i) spf[j] = min(spf[j], i);

phi[1] = 1;
for(int i=2; i<=X; i++) phi[i] = (spf[i] == spf[i/spf[i]]) ? phi[i/spf[i]]*spf[i] : phi[i/spf[i]]*(spf[i]-1);

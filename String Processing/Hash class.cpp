/**
* A hashing helper class to compute hashes on arrays/strings
* Hashing can be used instead of the usual string processing algorithms
* like KMP and Z, to test equality of substrings etc.. in O(1)
* Using big and multiple prime numbers as bases, the probability of failure becomes nearly null
*/

struct Hash{
    vector<int> h;
    const int p = 2e4;
    Hash(int val[], int n){
        h.clear();
        int curH = 0;
        int curP = 1;
        for(int i = 0; i < n; ++i){
            curH = add(curH, mul(val[i],curP));
            curP = mul(curP, p);
            h.emplace_back(curH);
        }
    }
    int rangeHash(int l, int r){
        int b = h[r];
        int a = (l == 0) ? 0 : h[l-1];
        return mul(add(b,-a),inv(powM(p,l)));
    }
};
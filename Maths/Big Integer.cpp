/*
* A Big Integer type for C++, similar to "BigInt" in Java
* Supports basic arithmetic(+ - * /), modulos, greatest common divisor etc..
* Numbers are stored as strings so it can handle numbers having MILLIONS of digits
*/

struct BigInt {
	static const int base = 1e9, base_digits = 9;
    vector<int> num; int sign;
    BigInt() : sign(1) {}
    BigInt(const int& v) {*this = v;}
    BigInt(const string &s) {
        sign = 1;
        num.clear();
        int pos = 0;
        while (pos < (int) size(s) && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = size(s) - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++) x = x * 10 + s[j] - '0';
            num.emplace_back(x);
        }
        trim();
    }

	friend ostream& operator>>(ostream &stream, const BigInt &v);
	friend ostream& operator<<(ostream &stream, const BigInt &v);
	string toString(){ stringstream ss; ss << *this; string s; ss >> s; return s; }

	// friend BigInt gcd(const BigInt &u, const BigInt &v);
	// friend BigInt lcm(const BigInt &u, const BigInt &v);

    int nbDigits(){
        if(num.empty()) return 0;
        int ans=(size(num)-1)*base_digits;
        int last=num.back();
        while(last) ans++,last/=10;
        return ans;
    }
	int sumDigits(){
        if(num.empty()) return 0;
        int ans=0;
        for(int d: num){
			int tmp = d;
			while(tmp) ans+=tmp%10, tmp/=10;
		}
        return ans;
    }
	bool isZero() const {return num.empty() || (size(num) == 1 && !num[0]);}
    BigInt operator-() const { BigInt res = *this; res.sign = -sign; return res; }
	BigInt abs() const { BigInt res = *this; res.sign *= res.sign; return res; }

	//  operations with bigints
	void operator=(const BigInt &v) { sign = v.sign; num = v.num; }
    BigInt operator+(const BigInt &v) const {
        if(sign != v.sign) return *this - (-v);
        BigInt res = v;
        for (int i = 0, carry = 0; i < (int) max(size(num), size(v.num)) || carry; ++i) {
            if (i == (int) size(res.num)) res.num.emplace_back(0);
            res.num[i] += carry + (i < (int) size(num) ? num[i] : 0);
            carry = res.num[i] >= base;
            if (carry) res.num[i] -= base;
        }
        return res;
    }
    BigInt operator-(const BigInt &v) const {
		if(sign != v.sign) return *this + (-v);
        if (abs() >= v.abs()) {
            BigInt res = *this;
            for (int i = 0, carry = 0; i < (int) size(v.num) || carry; ++i) {
                res.num[i] -= carry + (i < (int) size(v.num) ? v.num[i] : 0);
                carry = res.num[i] < 0;
                if (carry) res.num[i] += base;
            }
            res.trim();
            return res;
        }
        return -(v - *this);
    }
	typedef vector<long long> vll;
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vll p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) size(p); i++) p[i] = p[i - 1] * 10;
        vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) size(a); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.emplace_back(cur % p[new_digits]);
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.emplace_back(cur);
        while (!res.empty() && !res.back()) res.pop_back();
        return res;
    }
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = size(a);
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) res[i + j] += a[i] * b[j];
            return res;
        }
 
        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());
 
        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);
 
        for (int i = 0; i < k; i++) a2[i] += a1[i];
        for (int i = 0; i < k; i++) b2[i] += b1[i];
 
        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) size(a1b1); i++) r[i] -= a1b1[i];
        for (int i = 0; i < (int) size(a2b2); i++) r[i] -= a2b2[i];
 
        for (int i = 0; i < (int) size(r); i++) res[i + k] += r[i];
        for (int i = 0; i < (int) size(a1b1); i++) res[i] += a1b1[i];
        for (int i = 0; i < (int) size(a2b2); i++) res[i + n] += a2b2[i];
        return res;
    }
    BigInt operator*(const BigInt &v) const {
        vector<int> a6 = convert_base(this->num, base_digits, 6);
        vector<int> b6 = convert_base(v.num, base_digits, 6);
       
        vll aa(a6.begin(), a6.end());
        vll bb(b6.begin(), b6.end());
       
        while (size(aa) < size(bb)) aa.emplace_back(0);
        while (size(bb) < size(aa)) bb.emplace_back(0);
        while (size(aa) & (size(aa) - 1)) aa.emplace_back(0), bb.emplace_back(0);
           
        vll c = karatsubaMultiply(aa, bb);
        BigInt res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) size(c); i++) {
            long long cur = c[i] + carry;
            res.num.emplace_back(cur % 1000000);
            carry = (int) (cur / 1000000);
        }
        res.num = convert_base(res.num, 6, base_digits);
        res.trim();
        return res;
    }
	pair<BigInt, BigInt> divmod(const BigInt &a1, const BigInt &b1) {
        int norm = base / (b1.num.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q, r;
        q.num.resize(size(a.num));
 
        for (int i = size(a.num) - 1; i >= 0; i--) {
            r *= base;
            r += a.num[i];
            int s1 = size(r.num) <= size(b.num) ? 0 : r.num[size(b.num)];
            int s2 = size(r.num) <= size(b.num) - 1 ? 0 : r.num[size(b.num) - 1];
            int d = (int) ((long long) base * s1 + s2) / b.num.back();
            r -= b * d;
            while (r < 0)
                r += b, --d;
            q.num[i] = d;
        }
 
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    BigInt operator/(const BigInt &v) {return divmod(*this, v).first;}
    BigInt operator%(const BigInt &v) {return divmod(*this, v).second;}
	void operator+=(const BigInt &v) {*this = *this + v;}
    void operator-=(const BigInt &v) {*this = *this - v;}
    void operator*=(const BigInt &v) {*this = *this * v;}
    void operator/=(const BigInt &v) {*this = *this / v;}
    void operator%=(const BigInt &v) {*this = *this % v;}
    
	//  operations with integers                                         CHANGE TO LONG LONG IF NEEDED
	BigInt operator+(const int& v) const {return *this + BigInt(v);}
	void operator+=(const int& v) {*this = *this + v;}
	BigInt operator-(const int& v) const {return *this - BigInt(v);}
    void operator-=(const int& v) {*this = *this - v;}
	void operator=(int v) {
        sign = 1; num.clear();
        if (v < 0) sign = -sign, v = -v;
        for (; v>0; v/=base) num.emplace_back(v % base);
    }
	void operator*=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) size(num) || carry; ++i) {
            if (i == (int) size(num)) num.emplace_back(0);
            long long cur = (long long)num[i] * v + carry;
            carry = (int) (cur / base);
            num[i] = (int) (cur % base);
        }
        trim();
    }
    BigInt operator*(int v) const { BigInt res = *this; res *= v; return res; }
	void operator/=(int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = (int) size(num) - 1, rem = 0; i >= 0; --i) {
            long long cur = num[i] + (long long) rem * base;
            num[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }
    BigInt operator/(int v) const { BigInt res = *this; res /= v; return res; }
	void operator%=(int v) {*this = *this % v;}
    int operator%(int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (int i = size(num) - 1; i >= 0; --i) m = (num[i] + (long long) m * base) % v;
        return m * sign;
    }
 
    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (size(num) != size(v.num)) return size(num) * sign < size(v.num) * v.sign;
        for (int i = size(num) - 1; i >= 0; i--)
            if (num[i] != v.num[i]) return num[i] * sign < v.num[i] * sign;
        return false;
    }
    bool operator>(const BigInt &v) const {return v < *this;}
    bool operator<=(const BigInt &v) const {return !(v < *this);}
    bool operator>=(const BigInt &v) const {return !(*this < v);}
    bool operator==(const BigInt &v) const {return !(*this < v) && !(v < *this);}
    bool operator!=(const BigInt &v) const {return *this < v || v < *this;}

    void trim() { while (!num.empty() && !num.back()) num.pop_back(); if (num.empty()) sign = 1; }
    int value() const {
        int res = 0;
        for (int i = size(num) - 1; i >= 0; i--) res = res * base + num[i];
        return res * sign;
    }
};
istream& operator>>(istream &stream, BigInt &v) { string s; stream >> s; v = BigInt(s); return stream; }
ostream& operator<<(ostream &stream, const BigInt &v) {
	if (v.sign == -1) stream << '-';
	stream << (v.num.empty() ? 0 : v.num.back());
	for (int i = (int) size(v.num) - 2; i >= 0; --i) stream << setw(BigInt::base_digits) << setfill('0') << v.num[i];
	return stream;
}
BigInt gcd(BigInt &a, BigInt &b) {return b.is_zero() ? a : gcd(b, a % b);}
BigInt lcm(BigInt &a, BigInt &b) {return a / gcd(a, b) * b;}
/**
* A widely used algorithm in Maths
* The most known use to it in Competitive Programming is the 
* ability to multiply two polynomials f and g of size N each
* in O(N*log(N))
*/

namespace FFT{
	void fft(vector<complex<LD>>& a, bool invert) {
		int n = size(a);
		if(n == 1) return;
		vector<complex<LD>> y0(n/2), y1(n/2);
		for (int i = 0, j = 0; i < n; i += 2, ++j) {
			y0[j] = a[i];
			y1[j] = a[i + 1];
		}

		fft(y0, invert);
		fft(y1, invert);

		LD ang = ((2.0 * PI) / n) * (invert ? -1 : 1);
		complex<LD> w(1) , wn(cos(ang), sin(ang));

		for (int k = 0; k < n / 2; ++k) {
			a[k] = y0[k] + w * y1[k];
			a[k + n / 2] = y0[k] - w * y1[k];

			if (invert) a[k] /= 2 , a[k + n / 2] /= 2;
			w *= wn;
		}
	}
	void multiply(vector<int>& a , vector<int>& b, vector<int>& res) {
		int n = 1;
		while (n < max(size(a) , size(b))) n <<= 1;
		n <<= 1;

		vector<complex<LD>> fx(all(a)) , fy(all(b));
		fx.resize (n) , fy.resize (n);
		fft(fx, false) , fft(fy, false);

		vector<complex<LD>> hx(n);
		for (int i = 0; i < n; ++i) hx[i] = fx[i] * fy[i];
		fft(hx, true);

		res.resize(n);
		for (int i = 0; i < n; ++i)
			res[i] = int (hx[i].real() + 0.5);
	}
};

int main(){
      vector<int> f = {1,1,1} , g = {1,3};
      // f(x) = 1 + x + x^2   ---   g(x) = 1 + 3x

      vector<int> res;
      multiply(f , g , res);

      for(int i = 0; i < sz(res); i++)
            cout << res[i] << ' ';

      return 0;
}

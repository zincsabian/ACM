// #define double long double
// #define ll __int128 
//精度不够的时候要开int128和long double
//空间要开4倍 多项式长度2n， 扩域最多到4n
const int N = 1<<20;
typedef vector<ll> poly;
typedef complex<double> Complex;
const double pi = acos(-1);
const int L = 15, MASK = (1<<L) - 1;
Complex rev[N+7];
void FFT_init(int n){
	for(int i=0; i<n; i++)
		rev[i] = Complex(cos(2*i*pi/n), sin(2*i*pi/n));
}
void FFT(Complex *p, int n){
	for(int i=1, j=0; i<n-1; i++){
		for(int s=n; j^=s>>=1, ~j&s;);
		if(i<j) swap(p[i], p[j]);
		//依旧是蝴蝶变换， 没有什么不一样
	}
	for(int d=0; (1<<d)<n; d++){
		int m = 1<<d, m2 = m<<1, rm = n >> (d+1);
		for(int i=0; i<n; i+=m2)
			for(int j=0; j<m; j++){
				Complex &p1 = p[i+j+m], &p2 = p[i+j];
				Complex t = rev[rm*j]*p1;
				p1 = p2 - t; p2 = p2 + t;
			}
	}
}
Complex A[N+7], B[N+7], C[N+7], D[N+7];
//拆系数fft || 任意模数ntt
poly operator*(poly &a, poly &b){
	int n = a.size()-1, m = b.size()-1;
	for(m+=n, n=1; n<=m; n<<=1);
	FFT_init(n);
	a.resize(n); b.resize(n);
	for(int i=0; i<n; i++){
		A[i] = Complex(a[i]>>L, a[i]&MASK);
		B[i] = Complex(b[i]>>L, b[i]&MASK);//拆成两部分
	}
	FFT(A, n); FFT(B, n);
	for(int i=0; i<n; i++){
		int j = (n-i)%n;
		//conj表示返回一个complex的共轭
		//压缩值域， 前一半和后一半
		Complex da = (A[i] - conj(A[j])) * Complex(0,-0.5),//实部
				db = (A[i] + conj(A[j])) * Complex(0.5, 0),//虚部
				dc = (B[i] - conj(B[j])) * Complex(0,-0.5),
				dd = (B[i] + conj(B[j])) * Complex(0.5, 0);
		C[j] = da*dd+da*dc*Complex(0, 1);//进行复合
		D[j] = db*dd+db*dc*Complex(0, 1);
	}
	FFT(C, n); FFT(D, n);
	poly res(n);
	for(int i=0; i<n; i++){
		ll da = (ll)(C[i].imag()/n+0.5) % mod,
		   db = (ll)(C[i].real()/n+0.5) % mod,
		   dc = (ll)(D[i].imag()/n+0.5) % mod,
		   dd = (ll)(D[i].real()/n+0.5) % mod;
		res[i] = (((dd<<(L<<1))%mod + ((db+dc)<<L)%mod)%mod + da) % mod;
	}
	res.resize(m+1);
	return res;
}
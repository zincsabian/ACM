#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
#define ln '\n'

//FFT多项式乘法
//n和m表示两个多项式的次数
//a[i].x和b[i].x表示第i项
//结果保存在a[i].x中， 注意是浮点数， 需要取整输出
const int N = 1<<20;
// #define double long double
const double pi = acos(-1);
typedef vector<ll> poly;
//根据精度判断double还是long double
//long double可能会导致速度变慢
//#define double long double
struct com{//复数
	com(double xx=0, double yy=0){x=xx; y=yy;}
	double x, y;
	com operator +(com const &b) const{
		return com(x+b.x, y+b.y);
	}
	com operator -(com const &b) const{
		return com(x-b.x, y-b.y);
	}
	com operator *(com const &b) const {
		return com(x*b.x-y*b.y, x*b.y+b.x*y);
	}
	com conj(){return com(x, -y);}
}A[N<<1], B[N<<1], rev[N<<1];

const int L = N<<1;
inline void fft_init(){
	for(int i=0; i<N<<1; i++)
		rev[i] = com(cos(2*i*pi/L), sin(2*i*pi/L));
}

void fft(com *f, int n, int flag){
	for(int i=(n>>1), j=1; j<n; j++){
		if(i<j) swap(f[i], f[j]);
		int k = (n>>1);
		while(i&k){i^=k; k>>=1;}
		i^=k;//蝴蝶变换
	}
	for(int k=2; k<=n; k<<=1){
		// com rt(cos(2*pi/k), sin(2*pi/k)*flag);//单位根
		//dft && idft
		int rt = L/k;
		for(int i=0; i<n; i+=k){
			int w = 0;
			for(int j=i; j<(i+(k>>1)); j++){
				com u = f[j], v = f[j+(k>>1)] * (flag == 1?rev[w]:rev[w].conj());
				f[j] = u+v;
				f[j+(k>>1)] = u-v;
				w = w + rt;
			}
		}
	}
	if(flag == -1){//idft
		for(int i=0; i<n; i++)
			f[i].x=f[i].x/n;
	}
}

poly operator*(poly a, poly b){
	int n = a.size() - 1, m = b.size() - 1;
	for(m+=n, n=1; n<=m; n<<=1);
	a.resize(n); b.resize(n);
	for(int i=0; i<n; i++)
		A[i] = com(a[i], 0),
		B[i] = com(b[i], 0);
	fft(A, n, 1); fft(B, n, 1);
	for(int i=0; i<n; i++)	
		A[i] = A[i] * B[i];
	fft(A, n, -1);
	poly c(m+1);
	for(int i=0; i<=m; i++){
		if(A[i].x > 0)
			c[i] = (ll)(A[i].x + 0.5);
		else
			c[i] = (ll)(A[i].x - 0.5);
	}
	return c; 
}

int main(){
	// freopen("0.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
   	cin >> n >> m;
   	fft_init();
   	poly a(n+1), b(m+1);
   	for(int i=0; i<=n; i++)
   		cin >> a[i];
   	for(int i=0; i<=m; i++)
   		cin >> b[i];
   	a = a * b;
   	for(int i=0; i<=n+m; i++)
   		cout << a[i] << " ";
}
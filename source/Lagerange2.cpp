//#pragma GCC optimize(2)
//#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
#define ln '\n'

const int mod = 998244353;
typedef vector<int> poly;
inline int power(int a, int b){
	int res = 1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)
			res=1ll*res*a%mod;
	return res;
}

inline int Inv(int x){return power(x, mod-2);}
//如果mod非质数需要换成exgcd

poly Lagrange(const poly &x, const poly &y){//插系数， x不连续， y连续
	int n = x.size();//n个点确定一个n+1次多项式
	poly a(n, 0), b(n+1, 0), c(n+1, 0), f(n, 0);
	for(int i = 0; i < n; i++){
		int A = 1;
		for(int j = 0; j < n; j++)
			if(i!=j)
				A = 1ll * A * (x[i] - x[j] + mod) % mod;
		//crt
		a[i] = 1ll * Inv(A) * y[i] % mod;
	}
	b[0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j; j--)
			b[j] = (1ll * b[j] * (mod - x[i]) % mod + b[j-1]) % mod;
		b[0] = 1ll * b[0] * (mod - x[i]) % mod;
	}
	for(int i = 0; i < n; i++){
		int inv = Inv(mod - x[i]);
		if(inv){
			c[0] = 1ll * b[0] * inv % mod;
			for(int j = 1; j <= n; j++)
				c[j] = 1ll * (b[j] + mod - c[j-1]) * inv % mod;
		} else {
			for(int j = 0; j < n; j++)
				c[j] = b[j + 1];
		}
		for(int j = 0; j < n; j++)
			f[j] = (f[j] + 1ll * a[i] * c[j] % mod) % mod;
	}
	return f;
}

inline int calc(int x, const poly &a){
	int ans = 0;
	int n = a.size(); --n;
	for(;~n;n--)
		ans = (1ll * ans * x % mod + a[n]) % mod;
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

}
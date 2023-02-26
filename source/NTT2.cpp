//#pragma GCC optimize(2)
//#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
#define ln '\n'

const int g=3;
const int mod = 998244353;

inline void inc(int &a, int b){
    a+=b;
    if(a>=mod) a-=mod;
    if(a<0) a+=mod;
}
inline void dec(int &a, int b){
    a-=b;
    if(a<0) a+=mod;
    if(a>=mod) a-=mod;
}

inline int power(int a, int b){
    int res = 1;
    for(; b; b>>=1, a=1ll*a*a%mod)
        if(b&1)
            res=1ll*res*a%mod;
    return res;
}

typedef vector<int> poly;
void ntt(int *a, int n, int flag){
    for(int i=(n>>1), j=1; j<n; j++){
        if(i<j) swap(a[i], a[j]);
        int k = (n>>1);
        while(i&k){i^=k; k>>=1;}
        i^=k;
    }
    for(int k=2; k<=n; k<<=1){
        int rt = power(g, (mod-1)/k);
        if(flag == -1) 
            rt = power(rt, mod-2);
        for(int i=0; i<n; i+=k){
            int del = 1;
            for(int j=i; j<i+k/2; j++){
                int u = a[j], v = 1ll * del * a[j+k/2] % mod;
                a[j] = (u + v) % mod;
                a[j+k/2] = (u - v + mod) % mod;
                del = 1ll * del * rt % mod;
            }
        }
    }
    if(flag == -1){
        int inv = power(n, mod-2);
        for(int i=0; i<n; i++)
            a[i] = 1ll * a[i] * inv % mod;
    }
}

poly operator*(poly a, poly b){
    int m = b.size(), n = a.size();
    for(m+=n, n=1; n<=m; n<<=1);
    a.resize(n); b.resize(n);
    ntt(a.data(), n, 1); ntt(b.data(), n, 1);
    for(int i=0; i<n; i++)
        a[i] = 1ll * a[i] * b[i] % mod;
    ntt(a.data(), n, -1);
    a.resize(m-1);
    return a;
}

poly operator*(poly a, int b){
    int m = a.size();
    for(int i=0; i<m; i++)
        a[i] = 1ll * a[i] * b % mod;
    return a;
}

poly operator*(int a, poly b){
    int m = b.size();
    for(int i=0; i<m; i++)
        b[i] = 1ll * b[i] * a % mod;
    return b;
}

poly operator+(poly a, poly b){
    int m = b.size(), n = a.size();
    a.resize(max(n, m));
    for(int i=0; i<b.size(); i++)
        inc(a[i], b[i]);
    return a;
}

poly operator-(poly a, poly b){
    int m = b.size(), n = a.size();
    a.resize(max(n, m));
    for(int i=0; i<b.size(); i++)
        dec(a[i], b[i]);
    return a;
}

void modxk(poly &a, int k){
    if(a.size() > k) a.resize(k);
}

poly Inv(poly &f){
    poly R{power(f[0], mod-2)};
    for(int i = 1; i<f.size(); i<<=1)
        R = 2*R-R*R*f, modxk(R, i<<1);
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    poly f(n);
    for(int i=0; i<n; i++)
        cin >> f[i];
    f = Inv(f);
    // f = inv(f);
    for(int i=0; i<n; i++)
        cout << f[i] << " ";
    cout << ln;
}
const int N=2e6+5;
const int mod = 20100403;
int n, m, fac[N], inv[N], cal[N];
inline int power(int a, int b){
    int res=1;
    while(b){
        if(b&1)
            res=1ll*res*a%mod;
        b>>=1;
        a=1ll*a*a%mod;
    }
    return res;
}
inline int C(int n, int m){
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void pre(int n){
    fac[0]=1;
    for(int i=1; i<=n; i++)
        fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=power(fac[n], mod-2);
    for(int i=n-1; i>=0; i--)
        inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void Caterlan(int n){
    return (C(2*n, n)-C(2*n, n-1)+mod)%mod
}
//51nod1275 连续子段的差异
//求满足最大值-最小值<=k的区间有多少个
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

inline ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch>'9'; ch = getchar())
        if(ch == '-') f = -f;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}

#define ln endl

const int N = 5e4+5;
int n, k, a[N], q[2][N], l[2], r[2];
ll ans;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w",stdout);
    #endif
    n=read(); k=read();
    l[1] = l[0] = r[1] = r[0] = 1;
    for(int i=1; i<=n; i++) 
        a[i] = read();
    int j = 1;
    q[1][l[1]] = q[0][l[0]] = 1;
    for(int i=1; i<=n; i++){//以i为左端点
        while(l[1] <= r[1] && q[1][l[1]] < i)
            l[1]++;
        while(l[0] <= r[0] && q[0][l[0]] < i)
            l[0]++;
        //把i往左的点都排掉
        while(j<=n && a[q[1][l[1]]] - a[q[0][l[0]]] <= k) {
            ++j;
            while(l[1] <= r[1] && a[q[1][r[1]]] <= a[j])
                --r[1];
            q[1][++r[1]] = j;
            while(l[0] <= r[0] && a[q[0][r[0]]] >= a[j])
                --r[0];
            q[0][++r[0]] = j;
        }
        ans = ans + (j-i);
        // printf("%d %d\n", i, j);
    }
    printf("%lld\n", ans);
}
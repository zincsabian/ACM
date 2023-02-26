//只有加法的莫队
//https://codeforces.com/contest/1514/problem/D
#include<bits/stdc++.h>
using namespace std;

#define ll long long

inline ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch>'9'; ch = getchar())
        if(ch == '-') f = -f;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}

inline void chkmin( int &a, int b ) { if(a > b) a = b; }

inline void chkmax( int &a, int b ) { if(a < b) a = b; }

#define _ read()

#define ln endl

const int N=3e5+5;
int n, m, siz, v[N], bl[N], res[N];
int l, r, R[1005], ans[N], cnt[N], tot[N];
vector<int> mo;
struct Mo{int l, r, id;}a[N];
inline bool cmp(Mo a, Mo b){return bl[a.l]==bl[b.l]?a.r<b.r:bl[a.l]<bl[b.l];}

inline void solve(int i){
    while(l<R[i]+1) cnt[v[l]]--, l++;
    while(r>R[i]) cnt[v[r]]--, r--;
    while(r<R[i]) ++r, cnt[v[r]]++;
    int tmp=0, res=0;
    for(int j=0; j<mo.size(); j++){
        int x=mo[j];
        while(r<a[x].r){
            r++; cnt[v[r]]++;
            res=max(res, cnt[v[r]]);
        }
        tmp=res;
        while(l>a[x].l){
            --l; cnt[v[l]]++;
            tmp=max(tmp, cnt[v[l]]);
        }
        ans[a[x].id]=max(2*tmp-(a[x].r-a[x].l+1), 1);
        while(l<R[i]+1) cnt[v[l]]--, ++l;
    }
    mo.clear();
}

int main(){
    n=read(); m=read(); siz=sqrt(n);
    for(int i=1; i<=n; i++) {
        v[i]=read(), bl[i]=(i-1)/siz+1;
        R[bl[i]]=max(R[bl[i]], i);
    }
    for(int i=1; i<=m; i++)
        a[i].l=read(), a[i].r=read(), a[i].id=i;
    sort(a+1, a+m+1, cmp);
    l=1; r=0;
    int lst=0;
    for(int i=1; i<=m; i++){
        if(bl[a[i].l]==bl[a[i].r]){
            int tmp=0;
            for(int j=a[i].l; j<=a[i].r; j++){
                tot[v[j]]++;
                if(tot[v[j]]>tmp) 
                    tmp=tot[v[j]];
            }
            ans[a[i].id]=max(2*tmp-(a[i].r-a[i].l+1), 1);
            for(int j=a[i].l; j<=a[i].r; j++)
                tot[v[j]]--;
        }else{
            if(bl[a[i].l]==lst);
            else if(mo.size()) solve(lst);
            mo.push_back(i); lst=bl[a[i].l];
        }
    }
    if(mo.size()) 
        solve(lst);
    for(int i=1; i<=m; i++)
        printf("%d\n", ans[i]);
}
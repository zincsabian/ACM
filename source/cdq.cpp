//最长上升子序列计数
//转化为偏序问题
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pb push_back
#define ln '\n'

const int N = 1e5+5;
const int mod = 1e9+7;
int n, a[N], id[N];
pii f[N];

pii calc (pii a, pii b){
    if(a.first < b.first) return b;
    if(a.first > b.first) return a;
    a.second += b.second;
    if(a.second >= mod)
        a.second -= mod;
    return a;
};

void work(int l, int r){
    if(l == r)
        return;
    int mid = l+r>>1;
    work(l, mid);
    for(int i=l; i<=r; i++)
        id[i] = i;
    sort(id+l, id+r+1, [](int x, int y){
        return a[x] == a[y] ? x > y : a[x] < a[y];
    });
    pair<int,int> now = {0,0};

    for(int i=l; i<=r; i++){
        if(id[i] <= mid)
            now = calc(now, f[id[i]]);
        else{
            auto tmp = now;
            tmp.first++;
            f[id[i]] = calc(f[id[i]], tmp);
        }
    }

    work(mid+1, r);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
       for(int i=1; i<=n; i++)
           f[i] = {1, 1};//最长， 数量

       work(1, n);
      pair<int,int> ans = {0, 0};
      for(int i=1; i<=n; i++)
          ans = calc(ans, f[i]);

      cout << ans.second << ln;
}
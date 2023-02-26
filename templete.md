# 图论

## 最短路径

效率$O(NlogM+M)$

```cpp
struct dijkstra{
    #define N 100005
    #define M 500005
    struct edge{
        int to, nxt, w;
    }e[M];

    int head[N], cnt;
    dijkstra(){clear();}

    inline void clear(){
        memset(head, 0, sizeof(head));
        cnt = 0;
    }

    inline void insert(int u, int v, double w){
        e[++cnt] = (edge){v, head[u], w};
        head[u] = cnt;
    }

    struct node{
        int id, dis;
        bool operator <(const node &b) const{
            return dis>b.dis;
        }
    };
    priority_queue<node> q;
    int vis[N], n,  dis[N];

    inline void dij(int st){
        for(int i=0; i<=n; i++)
            dis[i] = 2e9, vis[i] = 0;
        dis[st] = 0;
        q.push((node){0, st});
        while(!q.empty()){
            node now = q.top(); q.pop();
            if(vis[now.id])
                continue;
            vis[now.id] = 1;
            int id = now.id;
            for(int i=head[id]; i; i=e[i].nxt)
                if(dis[e[i].to] > now.dis + e[i].w)
                    dis[e[i].to] = now.dis + e[i].w,
                    q.push((node){dis[e[i].to], e[i].to});
        }
    }
};
```

## 二分图最大匹配

效率$O(NM)$

```cpp
const int N=1e4+5;
const int M=1e6+N;
int n;
int vis[M], from[M];
vector<int> v;
vector<std::vector<int>> e(N);
bool dfs(int x){//复杂度为O(增广路)
    for(int y:e[x])
        if(!vis[y]){
            vis[y]=1;
            if(!from[y]||dfs(from[y])){
                from[y]=x;
                return true;
            }
        }
    return false;
}
```

## 网络流--最大流

效率$O(N^2M)$

在二分图上可以达到$O(N\sqrt M)$

```cpp
struct DINIC{
    #define N 1005
    #define M 252005
    //使用的时候记得给n, s, t赋值;
    //调NM的大小
    int n, S, T;
    struct EDGE{
        int to, nxt, w;
    }e[M<<1];
    int head[N], cnt = 0;
    inline void clear(){
        cnt = 0; 
        for(int i=0; i<=n; i++)
            head[i] = -1;
    }

    inline void insert2(int u, int v, int w){
        e[cnt]=(EDGE){v, head[u], w};
        head[u]=cnt++;
    }
    inline void insert(int u, int v, int w){
        insert2(u, v, w);
        insert2(v, u, 0);
    }

    int d[N], lst[N];
    inline bool bfs(){//分层图
        for(int i=0; i<=n; i++)
            lst[i] = head[i], d[i] = 0;
        queue<int> q;
        q.push(S);
        d[S] = 1;
        while(!q.empty()){
            int now = q.front(); q.pop();
            for(int i=head[now]; ~i; i=e[i].nxt){
                int v = e[i].to;
                if(!d[v]&&e[i].w>0)
                    d[v] = d[now] + 1,
                    q.push(v);
            }
        }
        return d[T]>0;
    }
    inline int dfs(int x, int mn){//找增广路
        if(x==T)
            return mn;
        for(int& i=lst[x]; ~i; i=e[i].nxt){//当前弧
            if(d[e[i].to] == d[x] + 1 && e[i].w){
                int val = dfs(e[i].to, min(e[i].w, mn));
                if(val>0){
                    e[i].w -= val;
                    e[i^1].w += val;
                    return val;
                }
            }
        }
        return 0;
    }
    inline int dinic(){
        int ans = 0;
        while(bfs())
            while(int d = dfs(S, 1e9))//多路增广
                ans+=d;
        return ans;
    }

    #undef N
    #undef M
}NF;
```

# 数学

## 线性基

```cpp
struct node{
    int p[64];
    inline bool insert(ll x){
        for(int i=63; i>=0; i--)
            if(x&(1ll<<i)){
                if(!p[i]){p[i]=x; return 1;}
                x^=p[i];
            }
        return 0;
    }
    inline node merge(node a, node b){
        for(int i=0; i<=63; i++)
            a.insert(b.p[i]);
        return a;
    }
}a;
```

## 线性筛法

```cpp
const int N=1e6+5;
int vis[N], pri[N], phi[N], cnt;

inline void solve(int n){
    for(int i=1; i<=n; i++)
        vis[i]=1;
    cnt=0;
    vis[1]=0;
    phi[1]=1;
    for(int i=2; i<=n; i++){
        if(vis[i])
            pri[++cnt]=i, phi[i] = i-1;
        for(int j=1; j<=cnt&&i*pri[j]<=n; j++){
            vis[i*pri[j]]=0;
            if(i%pri[j])
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            else{
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
        }
    }
}
```

## 组合数

$O(N)$

```cpp
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
```

$O(N^2)$

```cpp
vector<vector<int>>C(n+2, vector<int>(n+2, 0));
C[0][0]=1;
for(int i=1; i<=n+1; i++){
    C[i][0]=1;
    for(int j=1; j<=i+1; j++)
        C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
}
```

### 卡特兰数

```
相关问题:
1. 括号匹配: 你有n个左括号，n个右括号，问有多少个长度为2n的括号序列使得所有的括号都是合法的

2. 进出栈问题
   有一个栈，我们有2n次操作，n次进栈，n次出栈，问有多少中合法的进出栈序列

3. 312排列
    一个长度为$n$的排列$\{a\}$，只要满足$i<j<k$且$a_j<a_k<a_i$就称这个排列为312排列,求n的全排列中不是312排列的排列个数

4. 不相交弦问题
    在一个圆周上分布着 2n个点，两两配对，并在这两个点之间连一条弦，要求所得的2n条弦彼此不相交的配对方案数

5. 从(1, 1)走到(n, n)且不穿过对角线有多少条路径
```

```cpp
inline void Caterlan(int n){
    return (C(2*n, n)-C(2*n, n-1)+mod)%mod
}
```

## 组合博弈

```
sg(x)=mex{sg(y)} y为x的可达状态点
游戏和的SG函数等于各个游戏SG函数的Nim和 
一般是把sg函数打印出来找规律(((((
nim: 
    先手必胜要求sg函数不为0
anti-nim: 
    先手必胜要求sg函数不为0且存在一个sg(x)>1 
    或所有sg(x)=1且有偶数个游戏
```

```cpp
void dfs(int x){
    if(vis[x]) return;
    vis[x]=1;
    vector<int> v; v.clear();
    for(int i=1; i<=16&&f[i]<=x; i++)
        dfs(x-f[i]), v.push_back(sg[x-f[i]]);
    for(int val: v)
        cnt[val]=1;
    for(int i=0; i<=16; i++)
        if(!cnt[i]){
            sg[x]=i; 
            break;
        }
    for(int val: v)
        cnt[val]=0;
}
```

# 其他

## 二分查找 ***useful algorithm***

1.记录答案型

```cpp
int ans=0;
while(l<=r)
    if(check(mid))
        ans=mid, l=mid+1;
    else
        r=mid-1;
return ans;
```

2.右侧答案可行型

```cpp
while(l<r){
    int mid=(l+r+1)>>1;
    if(check(mid))
        l=mid;
    else
        r=mid-1;
}
return l;
```

## 分治

#### 普通分治

```
把一个区间拆成两个区间来求解， 分解成， 两边的部分， 还有跨过中间的部分， 跟线段树的思想差不多

trick: 启发式分治， 从两端同时往中间找断点， 这样就算断点不在mid， 复杂度也是logn的

bzoj 
```

#### 线段树分治

```cpp
//bzoj 二分图
//实际上就是把一段有效的区间拆成log个区间
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define ln '\n'

inline ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch>'9'; ch = getchar())
        if(ch == '-') f = -f;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}

const int N = 1e5+5;
int n, m, T;
vector<pair<int,int>> e[N<<2];

void insert(int L, int R, int u, int v, int l, int r, int rt){
    if(L <= l && r <= R){
        e[rt].pb({u, v});
        return;
    }
    int mid = l+r>>1;
    if(L <= mid)
        insert(L, R, u, v, l, mid, rt << 1);
    if(R  > mid)
        insert(L, R, u, v, mid+1, r, rt << 1 | 1);
}

int f[N], col[N], val[N], siz[N];
int cnt, top;
pair<int,int> rub[N<<1];
int find(int x){
    if(f[x] == x) return col[x] = 0, x;
    int par = find(f[x]);
    col[x] = col[f[x]] ^ val[x];
    return par;
}
void add(int x, int y){
    if(cnt)
        cnt++;
    else {
        int fx = find(x), fy = find(y);
        if(fx != fy){
            if(siz[fx] > siz[fy])
                f[fy] = fx, val[fy] = col[x]^col[y]^1, siz[fx]+=siz[fy], rub[++top] = {fx, fy};
            else
                f[fx] = fy, val[fx] = col[x]^col[y]^1, siz[fy]+=siz[fx], rub[++top] = {fy, fx};
        } else {
            if(col[x] == col[y])
                cnt++;//奇环
            else 
                top++;//直接丢垃圾桶
        }
    }
}
void del(){
    if(cnt) cnt--;
    else {
        auto now = rub[top--];
        f[now.second] = now.second;
        col[now.second] = 0;
        siz[now.first]-=siz[now.second];
    }
}

int ans[N];
void dfs(int l, int r, int rt){
    for(int i = 0; i < e[rt].size(); i++){
        auto now = e[rt][i];
        add(now.first, now.second);
    }
    if(l == r) {
        ans[l] = cnt?0:1;
        for(int i = 0; i < e[rt].size(); i++)
            del();
        return;
    }
    int mid = l + r >> 1;
    dfs(l, mid, rt << 1);
    dfs(mid + 1, r, rt << 1 | 1);
    for(int i = 0; i < e[rt].size(); i++)
        del();
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w", stdout);
    #endif
    n = read(); m = read(); T = read();
    for(int i=1; i<=m; i++){
        int u=read(), v=read(), st=read(), ed=read(); --ed;
        if(st > ed) continue;
        insert(st, ed, u, v, 0, T, 1);
    }
    for(int i=1; i<=n; i++)
        f[i] = i, siz[i] = 1, col[i] = 0, val[i] = 0;
    dfs(0, T, 1);
    for(int i=1; i<=T; i++)
        puts(ans[i-1]?"Yes":"No");
}
```

#### cdq分治

```cpp
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
```

## 快速幂

```cpp
auto power = [&](int a, int b){
    int res=1;
    for(; b; a=1ll*a*a%mod, b>>=1)
        if(b&1)
            res=1ll*a*res%mod;
    return res;
};
```

## 倍增

### 倍增法求lca

```cpp
vector<int> dep(n+1, 0);
vector<vector<int>> fa(n+1, vector<int>(20, -1));

std::function<void(int, int)> dfs=[&](int u, int p){
    for(int j=1; j<=18; j++)
        if(~fa[u][j-1])
            fa[u][j]=fa[fa[u][j-1]][j-1];
    for(int v:e[u])
        if(v==p) continue;
        else 
            dep[v]=dep[u]+1,
            fa[v][0]=u, 
            dfs(v, u);
};

dfs(0, -1);

auto lca = [&](int u, int v){
    if(dep[u]<dep[v])
        swap(u, v);
    for(int j=18; ~j; j--)
        if(~fa[u][j]&&dep[fa[u][j]]>=dep[v])
            u=fa[u][j];
    if(u==v)
        return u;
    for(int j=18; ~j; j--)
        if(fa[u][j]==fa[v][j]||fa[u][j]==-1||fa[v][j]==-1);
        else
            u=fa[u][j], v=fa[v][j];
    return fa[u][0];
};
```

### 倍增法求RMQ/ST表

```cpp
vector<vector<int>> f(n, vector<int>(17, 0));
for(int i=0; i<n; i++)
    f[i][0] = a[i];

for(int j=1; j<17; j++){
    for(int i=0; i+(1<<j)-1<n; i++)
        f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
}

vector<int> lg(n+1);
for(int i=1; i<=n; i++)
    lg[i]=log(i)/log(2);

auto ask = [&](int l, int r){
    if(l>r) 
        swap(l,r);
    int len = r-l+1; len = lg[len];
    return max(f[l][len], f[r-(1<<len)+1][len]);
};
//查询是O(1)的

auto ask = [&](int l, int r){
    int ans = 2e9;
    for(int j=17; j>=0; j--)
        if(l+(1<<j)-1<=r)
            ans=min(ans, f[l][j]), l = l+(1<<j);
    return ans;
};
//查询是O(log)的
```

## 莫队

### 只有add操作的莫队

```cpp
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
/*
  离线， 按l的块排序， r升序排序
  如果al和ar在一个块内， 直接暴力， 效率sqrt(n)
  如果al,ar不同块， 假设l在T这个块上， 我们让l移到下一个块的头, r在T的尾， 相当于重新更新了一次数组
  我们只需要把r往右移， 可以发现只需要add的操作
  由于r是递增的， 只有l是乱序的， 而且l在sqrtn的范围内
  所以我们可以记录块内l..r节点的答案
*/
```

## 悬线法求最大子矩阵

```cpp
//51nod最大全1子矩阵
int ans = 0;
for(int i=1; i<=n; i++){
    int top = 0;
    for(int j=1; j<=m; j++){
        a[i][j] = read();
        if(!a[i][j])
            U[i][j] = 0;
        else 
            U[i][j] = U[i-1][j] + 1;
        while(top&&U[i][j]<=U[i][s[top]])
            top--;
        L[i][j] = s[top] + 1;
        s[++top] = j;
    }
    s[++top] = m+1;
    for(int j=m; j; j--){
        while(top&&U[i][j]<=U[i][s[top]])
            top--;
        R[i][j] = s[top] - 1;
        s[++top] = j;
    }
    for(int j=1; j<=m; j++)
        ans = max(ans, U[i][j]*(R[i][j]-L[i][j]+1));
}
printf("%d\n", ans);
```

# 数据结构

## 单调队列

```cpp
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
```

## 树状数组

```cpp
struct BIT{
    #define N 100005
    int t[N], n;
    inline void clear(){
        for(int i=1; i<=n; i++)
            t[i] = -1;
    }
    inline int lowbit(int x){return x&-x;}
    inline void insert(int x, int v){
        for(; x<=n; x+=lowbit(x))
            t[x]=max(t[x], v);
    }
    inline int ask(int x){
        int ans = 0;
        for(; x; x-=lowbit(x))
            ans = max(ans, t[x]);
        return ans;
    }
    #undef N
}T;
```

## 并查集

#### 普通并查集

```cpp
struct DSU{
    #define N 200005
    int f[N], n, siz[N];
    inline void clear(){for(int i=0; i<=n; i++) f[i]=i, siz[i]=1;}
    int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
    bool merge(int x, int y){
        int fx=find(x), fy=find(y);
        if(fx!=fy){    
            if(siz[fx]>=siz[fy])
                f[fy]=fx, siz[fx]+=siz[fy];
            else
                f[fx]=fy, siz[fy]+=siz[fx];
            return 1;
        }
        return 0;
    }
    #undef N
}g;
```

#### 可删除并查集

```cpp
//动态维护无向图的连通性
int f[N], siz[N];
int top;
pair<int,int> e[10*N];

int find(int x){
    if(f[x] == x) return f[x];
    int par = find(f[x]);
    return par;
}

void add(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        if(siz[fy] > siz[fx])
            siz[fy] += siz[fx], f[fx] = fy, e[++top] = {fy, fx};
        else
            siz[fx] += siz[fy], f[fy] = fx, e[++top] = {fx, fy};
        //最后一条边是谁往谁连的
        res--;
    } else 
        e[++top] = {0, 0};//已经联通那么实际上不需要加到图里
}

void del(){
    //删除最后一条边， 回复到上一次的状态
    auto now = e[top--];
    if(now.first) res++;
    siz[now.first] -= siz[now.second];
    f[now.second] = now.second;
}
```

## 线段树

```cpp
const int N=2e5+5;
int n, m, a[N];
struct node{ll sum, l, r, llen, rlen, lf, rf;}t[N<<2];
inline node merge(node x, node y){
    node ans=(node){0,x.l,y.r,0,0,0,0};
    ans.lf=(x.lf&y.lf);
    ans.rf=(x.rf&y.rf);
    if(a[x.r]>a[y.l]) ans.lf=0, ans.rf=0;
    ans.llen=x.llen; ans.rlen=y.rlen;
    if(x.lf&&(a[x.r]<=a[y.l]))
        ans.llen=x.llen+y.llen;
    if(y.rf&&(a[x.r]<=a[y.l]))
        ans.rlen=x.rlen+y.rlen;
    ans.sum=x.sum+y.sum;
    if(a[x.r]<=a[y.l])
        ans.sum=ans.sum+x.rlen*y.llen;
    return ans;
}
inline void build(int l, int r, int rt){
    t[rt].l=l; t[rt].r=r;
    if(l==r){
        t[rt].sum=t[rt].llen=t[rt].rlen=t[rt].lf=t[rt].rf=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
    t[rt]=merge(t[rt<<1], t[rt<<1|1]);
}
inline node query(int L, int R, int l, int r, int rt){
    if(L<=l&&r<=R)
        return t[rt];
    int mid=(l+r)>>1;
    if(L<=mid&&R>mid)
        return merge(query(L, R, l, mid, rt<<1), query(L, R, mid+1, r, rt<<1|1));
    if(L<=mid)
        return query(L, R, l, mid, rt<<1);
    if(R>mid)
        return query(L, R, mid+1, r, rt<<1|1);
}
inline void modify(int x, int l, int r, int rt){
    if(l==r){
        t[rt].l=l; t[rt].r=r;
        t[rt].sum=t[rt].llen=t[rt].rlen=t[rt].lf=t[rt].rf=1; 
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid)
        modify(x, l, mid, rt<<1);
    else
        modify(x, mid+1, r, rt<<1|1);
    t[rt]=merge(t[rt<<1], t[rt<<1|1]);
}
```

## 动态开点线段树

```cpp
/*
    维护一段递增的序列
    一开始是a[i]=i
    在线段树上二分， 找到最右的一个<T的数 和 最左的一个>T的数
    找数需要的点最多2e5+2e5个
    所以总共最多需要6e5个点
    区间修改
    单点查询需要的节点最多2e5个
    空间开ki*4即可
    单个点最多需要logN的深度， 也就是
*/
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

const int N=6e5+5;

int cnt;
struct node{
    int l, r, lson, rson, mn, mx, lzy;
}T[N<<5];

void up(int rt){
    T[rt].mn=min(T[T[rt].lson].mn, T[T[rt].rson].mn);
    T[rt].mx=max(T[T[rt].lson].mx, T[T[rt].rson].mx);
}

void down(int rt){
    // if(T[rt].lzy){
    if(!T[rt].lson)
        T[rt].lson=++cnt, 
        T[cnt]=(node){T[rt].l, T[rt].l+T[rt].r>>1, 0, 0, T[rt].l, T[rt].l+T[rt].r>>1, 0};
    if(!T[rt].rson)
        T[rt].rson=++cnt, 
        T[cnt]=(node){(T[rt].l+T[rt].r>>1)+1, T[rt].r, 0, 0, (T[rt].l+T[rt].r>>1)+1, T[rt].r, 0};
    T[T[rt].lson].mx+=T[rt].lzy;
    T[T[rt].rson].mx+=T[rt].lzy;
    T[T[rt].lson].mn+=T[rt].lzy;
    T[T[rt].rson].mn+=T[rt].lzy;
    T[T[rt].lson].lzy+=T[rt].lzy;
    T[T[rt].rson].lzy+=T[rt].lzy;
    T[rt].lzy=0;
    // }
}

void add(int L, int R, int v, int l, int r, int rt){//区间加法
    if(!rt) 
        T[rt=++cnt]=(node){l, r, 0, 0, l, r, 0};
    if(L<=l&&r<=R){
        T[rt].mx+=v, T[rt].mn+=v, T[rt].lzy+=v;
        return;
    }
    int mid=l+r>>1;
    down(rt);
    if(L<=mid)
        add(L, R, v, l, mid, T[rt].lson);
    if(R>mid)
        add(L, R, v, mid+1, r, T[rt].rson);
    up(rt);
}

int queryl(int x, int l, int r, int rt){//二分找到=r的点
    if(l==r)
        return l-(T[rt].mn>=x);
    int mid=l+r>>1;
    down(rt);
    if(T[T[rt].rson].mn<x)//右子树中有<x的点
        return queryl(x, mid+1, r, T[rt].rson);
    else
        return queryl(x, l, mid, T[rt].lson);
}

int queryr(int x, int l, int r, int rt){
    if(l==r)
        return l+(T[rt].mx<=x);//如果最右边的比x小的点都>=x
    int mid=l+r>>1;
    down(rt);
    if(T[T[rt].lson].mx>x)//左子树中有>x的点
        return queryr(x, l, mid, T[rt].lson);
    else
        return queryr(x, mid+1, r, T[rt].rson);
}

int query(int x, int l, int r, int rt){
    if(l==r)
        return T[rt].mx;
    int mid=l+r>>1;
    down(rt);
    if(x<=mid)
        return query(x, l, mid, T[rt].lson);
    else
        return query(x, mid+1, r, T[rt].rson);

}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.out","w", stdout);
    #endif
    int n=read();
    T[cnt=1]=(node){0, (int)1e9, 0, 0, 0, (int)1e9, 0};
    int lastans=0;
    while(n--){
        int Ti=read();
        int L=queryl(Ti, 0, (int)1e9, 1), R=queryr(Ti, 0, (int)1e9, 1);
        // printf("%d %d\n", L, R);
        if(L>=0)
            add(0, L, 1, 0, (int)1e9, 1); 
        if(R<=(int)1e9)
            add(R, (int)1e9, -1, 0, (int)1e9, 1);
        int m=read();
        while(m--){
            int x=(read()+lastans)%((int)1e9+1); //x=x+lastans;
            // printf("%d ", x);
            printf("%d\n", lastans=query(x, 0, (int)1e9, 1));
        }
    }
}
/*
    值域是0..1e9
*/
```

# 头文件相关

## 快读&&快输

```cpp
inline ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch>'9'; ch = getchar())
        if(ch == '-') f = -f;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}
inline void print(ll x){
    if(!x)
        return;
    print(x/10);
    putchar(x%10+'0');
}
inline void write(ll x){
    if(x<0) putchar('-'), x=-x;
    if(!x) putchar('0');
    print(x);
}
inline void writeln(ll x){
    write(x); putchar('\n');
}
```
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
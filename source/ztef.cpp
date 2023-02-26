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

const int N = 5e4+5;
struct node{int l, r; ll sum, lzy;}tree[N<<2];

void pushup(int rt){
	tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}

void pushdown(int rt){
	int l = tree[rt].l, r = tree[rt].r;
	if(tree[rt].lzy){
		int mid = l + r >> 1;
		tree[rt<<1].lzy += tree[rt].lzy;
		tree[rt<<1|1].lzy += tree[rt].lzy;
		tree[rt<<1].sum += 1ll * tree[rt].lzy * (mid - l + 1);
		tree[rt<<1|1].sum += 1ll * tree[rt].lzy * (r - mid);
		tree[rt].lzy = 0;
	}
}

void build(int l, int r, int rt){
	tree[rt].l = l; tree[rt].r = r;
	if(l == r)
		return;
	int mid=l+r>>1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
}

void modify(int L, int R, int v, int l, int r, int rt){
	if(L <= l && r <= R){
		tree[rt].sum += 1ll * (r - l + 1) * v;
		tree[rt].lzy += v;
		return;
	}
	int mid = l + r >> 1;
	pushdown(rt);
	if(L <= mid)
		modify(L, R, v, l, mid, rt<<1);
	if(R > mid)
		modify(L, R, v, mid+1, r, rt<<1|1);
	pushup(rt);
}

ll query(int L, int R, int l, int r, int rt){
	if(L <= l && r <= R)
		return tree[rt].sum;
	int mid = l + r >> 1;
	ll ans = 0;
	pushdown(rt);
	if(L<=mid)
		ans += query(L, R, l, mid, rt<<1);
	if(R>mid)
		ans += query(L, R, mid+1, r, rt<<1|1);
	return ans;
}

int n, m;
int opt[N], lef[N], rig[N], ans[N];
ll c[N];

void work(int l, int r, vector<int> now){
	if(l>r) return;
	if(l==r){ 
		for(auto i: now) 
			if(opt[i] == 2) 
				ans[i] = l; 
		return; 
	}
	int mid = l+r>>1;
	vector<int> L, R;
	for(auto i: now)
		if(opt[i] == 1){
			if(c[i] > mid)
				R.pb(i), modify(lef[i], rig[i], 1, 1, n, 1);
			else
				L.pb(i);
		} else {
			ll tmp = query(lef[i], rig[i], 1, n, 1);
			if(tmp >= c[i])//>mid的有>=k个， 说明答案在mid+1..r
				R.pb(i);
			else
				c[i] -= tmp,
				L.pb(i);
		}
	// now.clear();
	for(auto i: R)
		if(opt[i] == 1) 
			modify(lef[i], rig[i], -1, 1, n, 1);
	if(L.size())
		work(l, mid, L);
	if(R.size())
		work(mid+1, r, R);
	//对>=mid的修改+1, <的不用管-->没贡献
	//对于修改， 如果c>=mid
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w", stdout);
    #endif
    n=read(); m=read();
    build(1, n, 1);
    std::vector<int> now;
    for(int i=1; i<=m; i++){
    	opt[i] = read(); 
    	lef[i]=read(); 
    	rig[i]=read(); 
    	c[i]=read();
  		if(lef[i] > rig[i]) swap(lef[i], rig[i]);
  		now.pb(i);
  	}
    work(0, n, now);
    for(int i=1; i<=m; i++)
    	if(opt[i] == 2) printf("%d\n", ans[i]);
}
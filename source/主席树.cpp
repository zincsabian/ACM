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

const int N = 2e5 + 5;
int n, m, T[N];
int ls[N << 5], rs[N << 5], siz[N << 5], cnt;

inline void insert( int v, int l, int r, int x, int &y)
{
	y = ++cnt; siz[y] = siz[x] + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	ls[y] = ls[x]; rs[y] = rs[x];
	if(v <= mid)
		insert(v, l, mid, ls[x], ls[y]);
	else
		insert(v, mid + 1, r, rs[x], rs[y]);
}

inline int ask( int k, int l, int r, int x, int y)
{
	if(k > siz[y] - siz[x] + 1)
		return 0;
	if(l == r) 
		return l;
	int mid = (l + r) >> 1;
	if(siz[ls[y]] - siz[ls[x]] >= k)
		return ask(k, l, mid, ls[x], ls[y]);
	else
		return ask(k - siz[ls[y]] + siz[ls[x]], mid + 1, r, rs[x], rs[y]);
}

int main()
{
	n = _; m = _;
	for( int i = 1, x; i <= n; i++ ) 
		x = _, insert(x, -1000000000, 1000000000, T[i - 1], T[i]);
	while(m--)
	{
		int l = _, r = _, k = _;
		printf("%d\n", ask(k, -1000000000, 1000000000, T[l - 1], T[r]));
	}
}
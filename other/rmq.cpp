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

const int N=200005;
int n1, n2, n3, n4;
int a[N], b[N], c[N], d[N];
vector<int> v[N];
ll dp[2][N], f[N][22];

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w",stdout);
    #endif
    n1=read(); n2=read(); n3=read(); n4=read();
	for(int i=1; i<=n1; i++)
		a[i] = read();
	for(int i=1; i<=n2; i++)
		b[i] = read();
	for(int i=1; i<=n3; i++)
		c[i] = read();
	for(int i=1; i<=n4; i++)
		d[i] = read();

	for(int i=1; i<=n1; i++)
		dp[1][i] = a[i];

	// for(int i=1; i<=n1; i++)
	// 	printf("%d ", dp[1][i]);
	// putchar('\n');

	for(int i=1; i<=n1; i++)
		f[i][0] = dp[1][i];

	for(int j=1; j<=17; j++){
		for(int i=1; i+(1<<j)-1<=n1; i++)
			f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	}

	int m1 = read();
	for(int i=1; i<=m1; i++){
		int x=read(), y=read();
		v[y].pb(x);
	}

	// memset(dp[0], 0, sizeof(dp[0]));
	for(int i=1; i<=n2; i++){
		dp[0][i] = 2e18;
		int l = 1;
		sort(v[i].begin(), v[i].end());
		v[i].pb(n1+1);
		for(int x: v[i]){
			int r = x-1;
			if(l<=r){
				int len = r-l+1; len = log(len)/log(2);
				// printf("2=====%d %d %d %d %d\n", i, l, r, len, min(f[l][len], f[r-(1<<len)+1][len]));
				dp[0][i] = min(dp[0][i], min(f[l][len], f[r-(1<<len)+1][len])+b[i]);
			}
			l = x+1;
		}
		v[i].clear();
	}

	// for(int i=1; i<=n2; i++)
	// 	printf("%d ", dp[0][i]);
	// putchar('\n');

	//1->2

	for(int i=1; i<=n2; i++)
		f[i][0] = dp[0][i];

	for(int j=1; j<=17; j++){
		for(int i=1; i+(1<<j)-1<=n2; i++)
			f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	}

	int m2 = read();
	for(int i=1; i<=m2; i++){
		int x=read(), y=read();
		v[y].pb(x);
	}

	// memset(dp[0], 0, sizeof(dp[0]));
	for(int i=1; i<=n3; i++){
		dp[1][i] = 2e18;
		int l = 1;
		sort(v[i].begin(), v[i].end());
		v[i].pb(n2+1);
		for(int x: v[i]){
			int r = x-1;
			if(l<=r){
				int len = r-l+1; len = log(len)/log(2);
				dp[1][i] = min(dp[1][i], min(f[l][len], f[r-(1<<len)+1][len])+c[i]);
			}
			l = x+1;
		}
		v[i].clear();
	}

	// for(int i=1; i<=n3; i++)
	// 	printf("%d ", dp[1][i]);
	// putchar('\n');

	//2->3

	for(int i=1; i<=n3; i++)
		f[i][0] = dp[1][i];

	for(int j=1; j<=17; j++){
		for(int i=1; i+(1<<j)-1<=n3; i++)
			f[i][j] = min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	}

	int m3 = read();
	vector<int> v[N];
	for(int i=1; i<=m3; i++){
		int x=read(), y=read();
		v[y].pb(x);
	}

	// memset(dp[0], 0, sizeof(dp[0]));
	for(int i=1; i<=n4; i++){
		dp[0][i] = 2e18;
		int l = 1;
		sort(v[i].begin(), v[i].end());
		v[i].pb(n3+1);
		for(int x: v[i]){
			int r = x-1;
			if(l<=r){
				int len = r-l+1; len = log(len)/log(2);
				dp[0][i] = min(dp[0][i], min(f[l][len], f[r-(1<<len)+1][len])+d[i]);
			}
			l = x+1;
		}
		v[i].clear();
	}

	ll ans = 2e18;
	for(int i=1; i<=n4; i++)
		ans = min(ans, dp[0][i]);

	if(ans == 2e18)
		ans = -1;

	printf("%lld\n", ans);
}
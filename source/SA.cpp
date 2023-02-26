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

const int N=1e6+5;
char s[N];
int n, cnt[N], sa[N], sa2[N], rk[N<<1], rk2[N<<1];

inline void getSA(){
	for(int i=1; i<=n; i++)
		rk[i]=s[i], sa[i]=i;
	int m=max(n, 256);
	for(int i=1; i<=m; i++) cnt[i]=0;
	for(int i=1; i<=n; i++) cnt[rk[sa[i]]]++;
	for(int i=1; i<=m; i++)
		cnt[i]+=cnt[i-1];
	for(int i=n; i; i--)
		sa2[cnt[rk[sa[i]]]--]=sa[i];
	for(int i=1; i<=n; i++)
		sa[i]=sa2[i], sa2[i]=0;
	for(int w=1; w<=n; w<<=1){
		for(int i=1; i<=m; i++) cnt[i]=0;
		for(int i=1; i<=n; i++) cnt[rk[sa[i]+w]]++;
		for(int i=1; i<=m; i++)
			cnt[i]+=cnt[i-1];
		for(int i=n; i; i--)
			sa2[cnt[rk[sa[i]+w]]--]=sa[i];
		for(int i=1; i<=n; i++)
			sa[i]=sa2[i], sa2[i]=0;
		for(int i=1; i<=m; i++) cnt[i]=0;
		for(int i=1; i<=n; i++) cnt[rk[sa[i]]]++;
		for(int i=1; i<=m; i++)
			cnt[i]+=cnt[i-1];
		for(int i=n; i; i--)
			sa2[cnt[rk[sa[i]]]--]=sa[i];
		for(int i=1; i<=n; i++)
			sa[i]=sa2[i], sa2[i]=0;
		int tot=0;
		for(int i=1; i<=n; i++){
			if(rk[sa[i]]==rk[sa[i-1]]&&rk[sa[i]+w]==rk[sa[i-1]+w])
				rk2[sa[i]]=tot;
			else
				rk2[sa[i]]=++tot;
		}
		for(int i=1; i<=n; i++)
			rk[i]=rk2[i], rk2[i]=0;
	}
	for(int i=1; i<=n; i++)
		cout<<sa[i]<<" ";
	cout<<ln;
}

int main(){
	scanf("%s", s+1); n=strlen(s+1);
	getSA();
}
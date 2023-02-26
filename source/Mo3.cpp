#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
struct pos{int l,r,id;}q[50005];
int n,m,a[50005],vis[50005],be[50005];
ll ans[50005],Ans[50005];
inline ll gcd(ll a,ll b){ return b==0?a:gcd(b,a%b); }
bool cmp(pos a,pos b){return be[a.l]==be[b.l]?a.r<b.r:be[a.l]<be[b.l];}
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main() {
	n=read(); m=read(); int siz=sqrt(n-1)+1;
	for(int i=1;i<=n;i++) a[i]=read(),be[i]=(i-1)/siz+1;//scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i; 
	std::sort(q+1,q+m+1,cmp);
	int l=1,r=0;ll res=0;
	for(int i=1;i<=m;i++) {
		while(l<q[i].l) res=res-(1ll*(vis[a[l]]*(vis[a[l]]-1)/2-1ll*(vis[a[l]]-1)*(vis[a[l]]-2)/2)),vis[a[l++]]--;
		while(r>q[i].r) res=res-(1ll*(vis[a[r]]*(vis[a[r]]-1)/2-1ll*(vis[a[r]]-1)*(vis[a[r]]-2)/2)),vis[a[r--]]--;
		while(l>q[i].l) vis[a[--l]]++,res=res+(1ll*(vis[a[l]]*(vis[a[l]]-1)/2-1ll*(vis[a[l]]-1)*(vis[a[l]]-2)/2));
		while(r<q[i].r) vis[a[++r]]++,res=res+(1ll*(vis[a[r]]*(vis[a[r]]-1)/2-1ll*(vis[a[r]]-1)*(vis[a[r]]-2)/2));
		ans[q[i].id]=res; Ans[q[i].id]=1ll*(q[i].r-q[i].l+1)*(q[i].r-q[i].l)/2;
		if(l==r) ans[q[i].id]=0;
	}
	for(int i=1;i<=m;i++) {
		if(ans[i]==0) {puts("0/1");continue;}
		ll G=gcd(ans[i],Ans[i]);
		printf("%lld/%lld\n",ans[i]/G,Ans[i]/G);
	}
}
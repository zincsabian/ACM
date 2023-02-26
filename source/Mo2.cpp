#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
using std::sort;
const int N=5e4+5,M=1e6+5;
struct node{int l,r,id,cur;}q[N];
struct Node{int x,c,lst;}b[N];
int n,m,a[N],bl[N],siz,cnt,tot;
int l,r,ans,vis[M],Ans[N],lst[N];
inline void add(int x) {
	if(++vis[a[x]]==1)++ans;
}
inline void del(int x) {
	if(--vis[a[x]]==0)--ans;
}
inline void upd(int x,int v) {
	if(l<=x&&x<=r) del(x),a[x]=v,add(x);
	else	a[x]=v;
}
bool cmp(node a,node b) {
	if(bl[a.l]!=bl[b.l])
		return bl[a.l]<bl[b.l];
	if(bl[a.r]!=bl[b.r])
		return bl[a.r]<bl[b.r];
	return a.id<b.id;
}
int main() {
	scanf("%d%d",&n,&m);
	siz=pow(n,0.6666);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),lst[i]=a[i],bl[i]=(i-1)/siz+1;
	for(int i=1;i<=m;i++) {
		char s[10];
		scanf("%s",s);
		if(s[0]=='Q') {
			int l,r;
			scanf("%d%d",&l,&r);
			++cnt;
			q[cnt]=(node){l,r,cnt,tot};//q[i].cur表示位于第几次修改之后
		}else {
			int x,c;
			scanf("%d%d",&x,&c);
			b[++tot]=(Node){x,c,lst[x]}; lst[x]=c;
		}
	}
	l=1; r=0; ans=0;
	int now=0;
	sort(q+1,q+cnt+1,cmp);
	for(int i=1;i<=cnt;i++) {
		while(q[i].cur<now) {//多加了
			upd(b[now].x,b[now].lst);
			now--;
		}
		while(q[i].cur>now) {//少加了
			now++;
			upd(b[now].x,b[now].c);
		}
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		Ans[q[i].id]=ans;
	}
	for(int i=1;i<=cnt;i++)
		printf("%d\n",Ans[i]);
}
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

struct DINIC{
	#define N 3005
	#define M 200005
	int n, S, T;
	struct EDGE{
		int to, nxt, w;
	}e[M<<1];
	int head[N], cnt = 0;
	inline void clear(){
		cnt = 0; 
		memset(head, -1, sizeof(head));
	}
	DINIC(){clear();}

	inline void insert(int u, int v, int w){
		e[cnt]=(EDGE){v, head[u], w};
		head[u]=cnt++;
		e[cnt]=(EDGE){u, head[v], 0};
		head[v]=cnt++;
	}

	int d[N], lst[N];
	inline bool bfs(){//分层图
		memset(d, 0, sizeof(d));
		for(int i=1; i<=n; i++)
			lst[i] = head[i];
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
		for(int& i=lst[x]; ~i; i=e[i].nxt){//多路增广&&当前弧
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
	inline ll dinic(){
		ll ans = 0;
		while(bfs())
			ans+=dfs(S, 1e9);
		return ans;
	}

	#undef N
	#undef M
}NF;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w",stdout);
    #endif
    int m, n;
    while(~scanf("%d%d", &m, &n)){
    	NF.clear();
	    NF.n=n;
	    for(int i=1; i<=m; i++){
	    	int u=read(), v=read(), w=read();
	    	NF.insert(u, v, w);
	    	NF.insert(v, u, 0);
	    }
	    NF.S = 1; NF.T = n;
	    printf("%d\n", NF.dinic());
    }
}
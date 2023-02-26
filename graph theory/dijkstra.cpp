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

struct dijkstra{
	#define N 100005
	#define M 500005
	struct edge{
		int to, nxt;
		double w;
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
		double dis;
		int id;
		bool operator <(const node &b) const{
			return dis>b.dis;
		}
	};
	priority_queue<node> q;
	double dis[N];
	int vis[N], n;

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

inline double dist(int x, int y, int X, int Y){
	return sqrt((X-x)*(X-x)+(Y-y)*(Y-y));
}

inline void solve(){
	dijkstra G;
	int n = read(), val = read(), st = read(), ed = read();
	G.n = 4*n; //G.st = 0; G.ed = 4*n;
	vector<pair<int,int>> v[105];
	int x[10], y[10];
	for(int i=1; i<=n; i++){
		// vector<int> x, y;
		for(int j=1; j<=3; j++)
			x[j] = read(), y[j] = read();
		int pos = 0;
		for(int k=1; k<=3; k++){
			vector<pair<int,int>> q;
			for(int j=1; j<=3; j++)
				if(k!=j)
					q.pb(make_pair(x[j]-x[k], y[j]-y[k]));
			if(q[0].first*q[1].first+q[0].second*q[1].second == 0){
				q.pb(make_pair(q[0].first+q[1].first, q[0].second+q[1].second));
				v[i].pb(make_pair(x[k], y[k]));
				for(int j=0; j<3; j++)
					v[i].pb(make_pair(x[k]+q[j].first, y[k]+q[j].second));
				break;
			}
		}

		int t = read();
		for(int j=0; j<v[i].size(); j++)
			for(int k=0; k<v[i].size(); k++)
				G.insert(4*(i-1)+j, 4*(i-1)+k%4, 
					dist(v[i][j].first, v[i][j].second, v[i][k].first, v[i][k].second)*t);
	
		// for(auto pt: v[i])
		// 	printf("%d %d\n", pt.first, pt.second);
		// puts("======w======");
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(i!=j){
				for(int k=0; k<4; k++)
					for(int l=0; l<4; l++)
						G.insert(4*(i-1)+k, 4*(j-1)+l, dist(v[i][k].first, v[i][k].second, v[j][l].first, v[j][l].second)*val);
			}

	for(int j=0; j<4; j++)
		G.insert(0, 4*(st-1)+j, 0);
	for(int j=0; j<4; j++)
		G.insert(4*(ed-1)+j, 4*n, 0);
	G.dij(0);
	printf("%.1lf\n", G.dis[4*n]);
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("0.txt","w",stdout);
    #endif
    int T=read();
    while(T--)
    	solve();
}
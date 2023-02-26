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
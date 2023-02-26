//要先算好边需要多少， 点需要多少
//dinic复杂度为n^2m
template<typename T>
struct Dinic{
	int s, t, tot;
	T F;
	const T INF = 2e9;
	vector<int> head, d, lst;
	struct Edge{int to, nxt; T w;};
	vector<Edge> e;
	Dinic(int n, int m, int st, int ed){
		head.assign(n+1, -1);
		e.resize(m<<1); 
		d.resize(n+1);
		s = st; t = ed; tot = 0; F = 0;
	}
	inline int add(int u, int v, T w){
		e[tot]=(Edge){v, head[u], w};
		head[u] = tot++;
		if(u == s) F+=w;
		return tot-1;
	}
	inline int insert(int u, int v, T w){
		int tmp = add(u, v, w);
		add(v, u, 0);
		return tmp;
	}
	inline bool bfs(){
		d.assign(d.size(), 0);
		lst = head;
		queue<int> q;
		q.push(s); d[s] = 1;
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int i=head[u]; ~i; i=e[i].nxt){
				int v = e[i].to;
				if(!d[v] && e[i].w > 0){
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		return d[t] > 0;
	}
	int dfs(int x, int mn){
		if(x == t) return mn;
		for(int &i = lst[x]; ~i; i=e[i].nxt){
			if(d[e[i].to] == d[x]+1 && e[i].w){
				int val = dfs(e[i].to, min(e[i].w, mn));
				if(val > 0){
					e[i].w -= val;
					e[i^1].w += val;
					return val;
				}
			}
		}
		return 0;
	}
	inline T work(){
		T ans = 0;
		while(bfs())
			while(int d = dfs(s, INF))
				ans+=d;
		return ans;
	}
	inline bool check(){//判满流
		return work() == F;
	}
};
struct DCC{

	vector<vector<int>>e;
	vector<vector<int>>g;
	vector<int> dfn, low;
	stack<int> sta;
	int vcc, tot, n;
	//vcc: n+1~2n 方点 可以建Block Forest
	DCC(int nn){
		n = nn;
		e.resize(n+1); g.resize(n<<1|1);
		dfn.resize(n+1); low.resize(n+1);
		tot = 0;
		vcc = n;
	}
	void tarjan(int u, int fa){
		low[u] = dfn[u] = ++tot; sta.push(u);
		for(int v: e[u]){
			if(v == fa) continue;
			if(!dfn[v]){
				tarjan(v, u);
				low[u] = min(low[u], low[v]);
				if(low[v] >= dfn[u]){//u是割点
					vcc++;//vertice double connected conponents
					while(sta.top() != v){
						int x = sta.top(); sta.pop();
						g[vcc].pb(x); g[x].pb(vcc);
					}
					sta.pop();
					g[vcc].pb(v); g[v].pb(vcc);
					g[vcc].pb(u); g[u].pb(vcc);
				}
			} else //双联通不需要考虑横叉边
				low[u] = min(low[u], dfn[v]);
		}
	}
	inline int work(){
		int tot = 0;
		for(int i=1; i<=n; i++){
			if(!dfn[i]){
				if(!tot)
					tarjan(i, 0);
				++tot;
			}
		}
		return tot;
	}
};
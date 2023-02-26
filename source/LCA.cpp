int n, fa[N][18], dep[N];
vector<int> e[N];
void dfs(int u){
	dep[u] = dep[fa[u][0]] + 1;
	for(auto v: e[u]){
		if(v==fa[u][0]) continue;
		fa[v][0] = u;
		dfs(v);
	}
}
int LCA(int u, int v){
	if(dep[u] < dep[v])
		swap(u, v);
	for(int i=17; ~i; i--)
		if(dep[fa[u][i]] > dep[v]) u = fa[u][i];
	if(dep[u] > dep[v])
		u = fa[u][0];
	if(u == v) 
		return u;
	for(int i=17; ~i; i--)
		if(fa[u][i] && fa[v][i] && fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
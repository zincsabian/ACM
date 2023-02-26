struct DSU{
	vector<int>fa,siz;
	int tot;
	DSU(int n){
		fa.resize(n+1); 
		siz.resize(n+1);
		for(int i=1; i<=n; i++) 
			fa[i] = i, siz[i] = 1;
		tot = n;
	}
	int find(int x){return fa[x]==x?x:fa[x] = find(fa[x]);}
	bool merge(int x, int y){
		x = find(x); y = find(y);
		if(x == y) return false;
		if(siz[x] > siz[y])
			swap(x, y);
		fa[x] = y;
		siz[y] += siz[x];
		tot--;
		return true;
	}
};
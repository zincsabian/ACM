#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back
#define ln '\n'

const int N = 1e4+5;
const int M = 1e7+5;

vector<pii> e[N];

int n, m;
int a[N];
int val[N], vis[N], sz[N], sum, rt;
//作为重心的价值， 以及该点是否删了， 子树的大小
int res[M];//该长度的链是否出现
int ans[N];//各个询问的答案是否出现

void getroot(int u, int fa){
	sz[u] = 1; val[u] = 0;
	for(auto [v, w]: e[u]){
		if(vis[v] || v == fa) 
			continue;
		getroot(v, u);
		sz[u] = sz[u] + sz[v];
		val[u] = max(val[u], sz[v]);		
	}
	val[u] = max(val[u], sum - sz[u]);
	if(!rt || val[u] < val[rt])
		rt = u;
}

vector<int> vec;

void dfs(int u, int fa, int dist){
	if(dist > 10000000) return;
	vec.pb(dist);
	for(auto [v, w]: e[u])
		if(!vis[v] && v!=fa)
			dfs(v, u, dist+w);
}

void calc(int u, int fa){
	vector<int> p;
	for(auto [v, w]: e[u]){
		if(vis[v] || v == fa)
			continue;
		vec.clear();
		dfs(v, u, w);
		for(auto len: vec){
			for(int i=1; i<=m; i++)
				if(a[i]-len>=0&&res[a[i] - len])
					ans[i] = 1;
		}
		for(auto len: vec){
			res[len]=1;
			p.pb(len);
		}
	}
	for(auto len: p)
		res[len] = 0;
}

void work(int u, int fa){
	vis[u] = 1;
	calc(u, fa);
	for(auto [v, w]: e[u]){
		if(vis[v] || v == fa) 
			continue;
		sum = sz[v]; rt = 0;
		getroot(v, u);//找子树内的重心
		work(rt, u);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for(int i=1; i<n; i++){
    	int u, v, w;
    	cin >> u >> v >> w;
    	e[u].pb({v, w});
    	e[v].pb({u, w});
    }

    for(int i=1; i<=m; i++)
    	cin >> a[i];

    res[0] = 1;
    rt = 0; sum = n;
    getroot(1, -1);
    // cout << "root:= " << rt << ln;
    work(rt, -1);

    for(int i=1; i<=m; i++)
    	cout << (ans[i]?"AYE":"NAY") << ln;
    
}
template<typename T>
struct EK{
    const T INF = 2e18;
    T cost;
    struct Edge{int to, nxt, w, f;};
    vector<Edge>e;
    vector<bool> vis;
    vector<int> head, lst;
    vector<T> dis;
    int tot, s, t;
    EK(int n, int m, int st, int ed){
        head.assign(n+1, -1); 
        e.resize(m<<1); 
        dis.resize(n+1);  vis.resize(n+1); 
        s = st; t = ed; tot = 0; cost = 0;
    }
    inline int add(int u, int v, int w, int f){
        e[tot]=(Edge){v, head[u], w, f}; 
        head[u] = tot++;
        return tot-1;
    }
    inline int insert(int u, int v, int w, int f){
        int tmp = add(u, v, w, f);
        add(v, u, -w, 0);
        return tmp;
    }
    inline bool spfa(){
        queue<int> q;
        dis.assign(dis.size(), INF);
        vis.assign(vis.size(), false);
        dis[s] = 0; vis[s] = 1;
        lst = head;
        q.push(s);
        while(!q.empty()){
            int u = q.front(); q.pop(); 
            for(int i = head[u]; ~i; i = e[i].nxt){
                int v = e[i].to;
                if(e[i].f > 0 && dis[v] > dis[u] + e[i].w){
                    dis[v] = dis[u] + e[i].w;
                    if(!vis[v]){
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
            vis[u] = 0;
        }
        return dis[t] != INF;
    }
    int dfs(int u, int f){
        if(u == t || !f) return f;
        vis[u] = 1;
        int ans = 0;
        for(int &i=lst[u]; ~i; i=e[i].nxt){
            int v = e[i].to;
            if(e[i].f && dis[v] == dis[u] + e[i].w && !vis[v]){
                int val = dfs(v, min(e[i].f, f - ans));
                if(val){
                    e[i].f -= val;
                    e[i^1].f += val;
                    cost += val * e[i].w;
                    ans += val;
                    if(ans == f) break;
                }
            }
        }
        vis[u] = 0;
        return ans;
    }
    inline array<T,2> work(){
        T ans = 0;
        while(spfa()){
            T d = dfs(s, INF);
            ans += d;
        }
        return {ans, cost};
    }
};
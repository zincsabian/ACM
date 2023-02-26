struct SCC{
//SCC(n) n:点数
    vector<vector<pii>>e;
    stack<int>sta;
    vector<int>id,dfn,low,ins,siz;
    vector<ll>val;
    int tot, scc, n;
    SCC(int nn){
        n = nn;
        e.resize(n+1); siz.resize(n+1);
        id.resize(n+1); dfn.resize(n+1);
        low.resize(n+1); ins.resize(n+1); val.resize(n+1);
        scc = tot = 0;
    }
    void tarjan(int u){
        dfn[u] = low[u] = ++tot; 
        sta.push(u); ins[u] = 1;
        for(pii E: e[u]){
            int v = E.first;
            if(!dfn[v]){
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if(ins[v]){
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]){
            ++scc;
            while(sta.top()!=u){
                int v = sta.top(); sta.pop();
                id[v] = scc;
                siz[scc]++;
                ins[v] = 0;
            }
            ins[u] = 0;
            id[u] = scc;
            siz[scc]++;
            sta.pop();
        }
    }
    inline void remake(){
        for(int i=1; i<=n; i++)
            if(!dfn[i]) tarjan(i);
        vector<vector<pii>> g(n+1);
        for(int u=1; u<=n; u++)
            for(pii E: e[u]){
                int v = E.first, w = E.second;
                if(id[u] != id[v])
                    g[id[u]].pb({id[v], w});//边权
                else
                    val[id[u]] += w;//点权
            }
        e = g;
    }
}; 

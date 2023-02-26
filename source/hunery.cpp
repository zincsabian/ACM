const int N=1e4+5;
const int M=1e6+N;
int n;
int vis[M], from[M];
vector<int> v;
vector<std::vector<int>> e(N);
bool dfs(int x){
    for(int y:e[x])
        if(!vis[y]){
            vis[y]=1;
            if(!from[y]||dfs(from[y])){
                from[y]=x;
                return true;
            }
        }
    return false;
}
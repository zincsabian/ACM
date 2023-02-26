//动态维护无向图的连通性
int f[N], siz[N];
int top;
pair<int,int> e[10*N];

int find(int x){
    if(f[x] == x) return f[x];
    int par = find(f[x]);
    return par;
}

void add(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        if(siz[fy] > siz[fx])
            siz[fy] += siz[fx], f[fx] = fy, e[++top] = {fy, fx};
        else
            siz[fx] += siz[fy], f[fy] = fx, e[++top] = {fx, fy};
        //最后一条边是谁往谁连的
        res--;
    } else 
        e[++top] = {0, 0};//已经联通那么实际上不需要加到图里
}

void del(){
    //删除最后一条边， 回复到上一次的状态
    auto now = e[top--];
    if(now.first) res++;
    siz[now.first] -= siz[now.second];
    f[now.second] = now.second;
}
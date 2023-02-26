const int N = 505;
const int inf = 2e9+233;

int n, nl, nr, m, x, y, z;
int g[N][N]; 

//nl: 左部图点数
//nr: 右部图点数
//g: 二分图边权
namespace KM{
	int left[N], right[N];
	int visl[N], visr[N];
	int lx[N], ly[N], slack[N];

	bool augment(int x){
		visl[x] = 1;
		for(int y = 1; y <= n; y++)
			if(visr[y]) continue;
			else {
				int slk = lx[x] + ly[y] - g[x][y];
				if(!slk){
					visr[y] = 1;
					if(!right[y] || augment(right[y])){
						right[y] = x; left[x] = y;
						return 1;
					}
				} else 
					slack[y] = min(slack[y], slk);
			}
		return 0;
	}

	void solve(){
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				ly[j] = max(ly[j], g[i][j]);
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++)
				visl[j] = visr[j] = 0, slack[j] = inf;
			if(augment(i)) continue;
			while(1){
				int d = inf, x;
				for(int j = 1; j <= n; j++)
					if(!visr[j]) d = min(d, slack[j]);
					
				for(int j = 1; j <= n; j++){
					if(!visr[j]){
						ly[j] -= d;
						slack[j] -= d;
						if(!slack[j]) x = j;
					}
					if(!visl[j]) 
						lx[j] += d;
				}
				
				if(!right[x]) break;
				visr[x] = 1; visl[right[x]] = 1;
				x = right[x];
				for(int y = 1; y <= n; y++)
					slack[y] = min(slack[y], 
						lx[x] + ly[y] - g[x][y]);
			}
			
			for(int j=1; j<=n; j++)
				visl[j] = visr[j] = 0;
			augment(i);
		}
	}

	void answer(){
		ll ans = 0;
		for(int i=1; i<=n; i++)
			ans += lx[i] + ly[i];
		cout << -ans << ln;
	}
}
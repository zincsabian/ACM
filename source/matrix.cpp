using Matrix = array<array<int,80>,80>;
using Vector = array<int,80>;
Vector operator *(Vector a, Matrix b){
	Vector res={0};
	for(int i=0; i<m; i++)
		for(int j=0; j<m; j++)
			inc(res[j], 1ll*a[i]*b[i][j]%mod);
	return res;
}
Vector operator *(Matrix b, Vector a){
	Vector res={0};
	for(int i=0; i<80; i++)
		for(int j=0; j<80; j++)
			inc(res[i], 1ll*a[j]*b[i][j]%mod);
	return res;
}
Matrix operator *(Matrix a, Matrix b){
	Matrix res={0};
	for(int i=0; i<80; i++)
		for(int j=0; j<80; j++)
			for(int k=0; k<80; k++)
				inc(res[i][j], 1ll*a[i][k]*b[k][j]%mod);
	return res;
}
Matrix power(Matrix a, ll b){
	Matrix res={0};
	for(int i=0; i<80; i++)
		res[i][i]=1;
	for(;b;b>>=1,a=a*a)
		if(b&1)
			res=res*a;
	return res;
}
inline void solve(){
	int n;
	cin >> n;
	Vector now={0};
	now[0] = 1;
	a = power(a, n);
	now = a * now;
}
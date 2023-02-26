//luogu P5656 二元一次不定方程
ll exgcd(int a, int b, ll &x, ll &y){
	if(b == 0){
		x = 1; y = 0;
		return a;
	}
	ll tx, ty;
	int d = exgcd(b, a % b, tx, ty);
	x = ty; y = tx - a / b * ty;
	return d;
}

inline ll calc(int a, int b){//excrt
	//t%N = a t % M = b
	//Nx+a=My+b=t
	int N = n<<1, M = m<<1;
	ll x, y;
	int d = exgcd(N, M, x, y);
	int c = b - a;
	if(c % d != 0) return 2e18;
	ll lcm = 1ll * N * M / d;
	x = 1ll * x * (b-a) / d % lcm;
	ll res = 1ll * x % lcm * N % lcm + a;
	res = (res + lcm) % lcm;
	if(res == 0) res = lcm;
	return res;
}

inline void solve(){
	int a, b, c;
	cin >> a >> b >> c;
	ll x, y;
	int d = exgcd(a, b, x, y);
	if(c % d)
		cout << -1 << ln;
	else {
		ll rx = x * c / d, ry = y * c / d;
		// cout << rx << " " << ry << ln;
		if(rx <= 0){

			ll tmp = abs(rx) / (b / d) + 1;
			rx += tmp * b / d;
			ry -= tmp * a / d;
			if(ry <= 0) {
				cout << rx << " ";

				tmp = abs(ry) / (a / d) + 1;
				ry += tmp * a / d;
				rx -= tmp * b / d;

				cout << ry << ln;
				return;
			}
		} else if(ry <= 0){
			ll tmp = abs(ry) / (a / d) + 1;
			ry += tmp * a / d;
			rx -= tmp * b / d;
			ll tmpy = ry;
			if(rx <= 0){

				tmp = abs(rx) / (b / d) + 1;
				rx += tmp * b / d;
				ry -= tmp * a / d;
				cout << rx << " " << tmpy << ln;

				return;
			}
		}
		// cout << rx << " " << ry << ln;
		
		ll L = -rx * d / b, R = ry * d / a;
		if(rx + L * b / d == 0) L++;
		if(ry - R * a / d == 0) R--;
		cout << R - L + 1 << " " << rx + L * b / d << " " << ry - R * a / d << " " << rx + R * b / d << " " << ry - L * a / d << ln;
		//rx <= ry

	}
} 
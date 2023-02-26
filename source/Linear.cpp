struct Linear{
//cnt != n说明可以构成0
    ll p[64];//根据数字的范围来开
    int cnt, n;
    Linear(){cnt = n = 0; for(int i=0; i<64; i++) p[i] = 0;}
    inline void clear(){cnt = n = 0; for(int i=0; i<64; i++) p[i] = 0;}
    inline void copy(Linear b){ 
    	for(int i=0; i<64; i++)
    		p[i] = b.p[i];
    }
    inline bool insert(ll x){
        ++n;
        for(int i=63; i>=0; i--)
            if(x&(1ll<<i)){
                if(!p[i]){p[i]=x; cnt++; return 1;}
                x^=p[i];
            }
        return 0;
    }
    inline ll query(ll x){
        if(cnt != n) --x;
        if(!x) return 0;
        ll res = 0;
        for(int i=0; i<64; i++)
            if(p[i]){
                if(x&1) res^=p[i];
                x>>=1;
            }
        if(x) return -1;
        return res;
    }
    inline ll mx(){//线性基最大值
    	ll res = 0;
    	for(int i=63; ~i; i--)
    		if(p[i] && (res^p[i]) > res) res^=p[i];
    	return res;
    }
};
inline Linear merge(Linear a, Linear b){
    for(int i=0; i<=63; i++)
        a.insert(b.p[i]);
    return a;
}
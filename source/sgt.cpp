//这个N得根据需要改成自己需要的值域大小
struct segtree {
	int l, r;
	ll mn, mx, sum;
}T[N<<2];
int tag[N<<2];
segtree operator +(segtree ls, segtree rs){
	segtree rt;
	rt.l = ls.l; rt.r = rs.r;
	rt.mx = max(ls.mx, rs.mx);
	rt.mn = min(ls.mn, rs.mn);
	rt.sum = ls.sum + rs.sum;
	return rt;
}
void pushup(int rt){
	T[rt] = T[rt<<1] + T[rt<<1|1];
}
void pushdown(int rt){
	if(tag[rt]){
		segtree &ls = T[rt<<1], &rs = T[rt<<1|1];
		ls.sum += 1ll*tag[rt]*(ls.r-ls.l+1);
		rs.sum += 1ll*tag[rt]*(rs.r-rs.l+1);
		ls.mx += tag[rt]; rs.mx += tag[rt];
		ls.mn += tag[rt]; rs.mn += tag[rt];
		tag[rt<<1] += tag[rt];
		tag[rt<<1|1] += tag[rt];
		tag[rt] = 0;
	}
}
void build(int l, int r, int rt){
	tag[rt] = 0;
	if(l == r){
		T[rt] = (segtree){l, l, 0, 0, 0};
		return;
	}
	int mid = l+r >> 1;
	build(l, mid, rt<<1);
	build(mid+1, r, rt<<1|1);
	pushup(rt);
}
void add(int L, int R, int v, int rt){
	int l = T[rt].l, r = T[rt].r;
	if(L <= l && r <= R)
		return T[rt].sum += 1ll*(r-l+1)*v, T[rt].mx += v, 
			T[rt].mn += v, tag[rt]+=v, void();
	int mid = l+r>>1;
	pushdown(rt);
	if(L <= mid) 
		add(L, R, v, rt<<1);
	if(R > mid)
		add(L, R, v, rt<<1|1);
	pushup(rt);
}
segtree query(int L, int R, int rt){
	int l = T[rt].l, r = T[rt].r;
	if(L <= l && r <= R)
		return T[rt];
	int mid = l+r>>1;
	pushdown(rt);
	if(L <= mid && R > mid)
		return query(L, R, rt<<1) + query(L, R, rt<<1|1);
	else if(L <= mid)
		return query(L, R, rt<<1);
	else
		return query(L, R, rt<<1|1);
}
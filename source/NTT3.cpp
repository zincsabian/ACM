#define Poly vector<int>
#define len(A) ((int) A.size())
namespace Pol {
    inline int add(int a, int b) { return (a += b) >= p ? a -= p : a; }
    inline int mul(int a, int b) { return 1ll * a * b % p; } 
    Poly operator - (const int &v, const Poly &a) {
        Poly res(a); 
        for (int i = 0; i < len(res); ++i) res[i] = p - res[i]; 
        res[0] = add(res[0], v); return res;
    }
    Poly operator - (const Poly &a, const int &v) {
        Poly res(a); res[0] = add(res[0], p - v); return res;
    }
    Poly operator * (const Poly &a, const int &v) {
        Poly res(a);
        for (int i = 0; i < len(res) ; ++i) res[i] = mul(res[i], v); 
        return res;
    }
 
    const int N = 4200000;
    const int G = 3;
    
    int P[N], inv[N], fac[N];
    void init_P(int n) {
        int l = 0; while ((1 << l) < n) ++l;
        for (int i = 0; i < n; ++i) P[i] = (P[i >> 1] >> 1) | ((i & 1) << l - 1);
    }
    void init_C() {
        if (fac[0]) return ;
        fac[0] = 1; 
        for (int i = 1; i < N; ++i) 
            fac[i] = mul(fac[i - 1], i);
        inv[N - 1] = pow_mod(fac[N - 1], p - 2); 
        for (int i = N - 2; ~i; --i) 
            inv[i] = mul(inv[i + 1], i + 1);
    }
    vector<int> init_W(int n) {
        vector<int> w(n); w[1] = 1;
        for (int i = 2; i < n; i <<= 1) {
            auto w0 = w.begin() + i / 2, w1 = w.begin() + i;
            int wn = pow_mod(G, (p - 1) / (i << 1));
            for (int j = 0; j < i; j += 2)
                w1[j] = w0[j >> 1], w1[j + 1] = mul(w1[j], wn);
        }
        return w; 
    } auto w = init_W(1 << 21);
    void DIT(Poly &a) {
        int n = len(a);
        for (int k = n >> 1; k; k >>= 1)
            for (int i = 0; i < n; i += k << 1)
                for (int j = 0; j < k; ++j) {
                    int x = a[i + j], y = a[i + j + k];
                    a[i + j + k] = mul(add(x, p - y), w[k + j])
                        , a[i + j] = add(x, y);
                }
    }
    void DIF(Poly &a) {
        int n = len(a); 
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0; i < n; i += k << 1)
                for (int j = 0; j < k; ++j) {
                    int x = a[i + j], y = mul(a[i + j + k], w[k + j]);
                    a[i + j + k] = add(x, p - y), a[i + j] = add(x, y);
                }
        int inv = pow_mod(n, p - 2);
        for (int i = 0; i < n; ++i) a[i] = mul(a[i], inv);
        reverse(a.begin() + 1, a.end());
    }
    Poly operator * (const Poly &A, const Poly &B) {
        int n = 1, n1 = len(A), n2 = len(B); 
        while (n < n1 + n2 - 1) 
            n <<= 1; 
        init_P(n);
        Poly a(n), b(n);
        for (int i = 0; i < n1; ++i) 
            a[i] = add(A[i], p);
        for (int i = 0; i < n2; ++i) 
            b[i] = add(B[i], p);
        DIT(a); DIT(b);
        for (int i = 0; i < n; ++i) 
            a[i] = mul(a[i], b[i]);
        DIF(a); a.resize(n1 + n2 - 1); return a; 
    }
    Poly MMul(const Poly &A, const Poly &B) { 
        // 差卷积, 默认 A 和 B 的长度相同
        int n = 1, L = len(A); while (n < 2 * L - 1) n <<= 1; init_P(n);
        Poly a(n), b(n);
        for (int i = 0; i < L; ++i) a[i] = add(A[i], p);
        for (int i = 0; i < L; ++i) b[i] = add(B[i], p);
        reverse(b.begin(), b.begin() + L);
        DIT(a); DIT(b);
        for (int i = 0; i < n; ++i) a[i] = mul(a[i], b[i]);
        DIF(a); a.resize(L); reverse(a.begin(), a.end()); return a; 
    }
    Poly Der(const Poly &a) {
        Poly res(a);
        for (int i = 0; i < len(a) - 1; ++i) res[i] = mul(i + 1, res[i + 1]);
        res[len(a) - 1] = 0; return res;
    }
    Poly Int(const Poly &a) {
        static int inv[N];
        if (!inv[1]) {
            inv[1] = 1; 
            for (int i = 2; i < N; ++i) inv[i] = mul(p - p / i, inv[p % i]);
        }
        Poly res(a); res.resize(len(a) + 1);
        for (int i = len(a); i; --i) res[i] = mul(res[i - 1], inv[i]);
        res[0] = 0; return res;
    }
    Poly Inv(const Poly &a) {
        Poly res(1, pow_mod(a[0], p - 2)); 
        int n = 1; while (n < len(a)) n <<= 1; 
        for (int k = 2; k <= n; k <<= 1) {
            int L = 2 * k; init_P(L); Poly t(L);
            copy_n(a.begin(), min(k, len(a)), t.begin()); 
            t.resize(L); res.resize(L);
            DIT(res); DIT(t);
            for (int i = 0; i < L; ++i) 
                res[i] = mul(res[i], add(2, p - mul(t[i], res[i])));
            DIF(res); res.resize(k);
        } res.resize(len(a)); return res;
    }
    Poly Offset(const Poly &a, int c) {
        int n = len(a); init_C();
        Poly t1(n), t2(n);
        for (int i = 0; i < n; ++i) t1[i] = mul(pow_mod(c, i), inv[i]);
        for (int i = 0; i < n; ++i) t2[i] = mul(a[i], fac[i]);
        t1 = MMul(t1, t2);
        for (int i = 0; i < n; ++i) t1[i] = mul(t1[i], inv[i]);
        return t1; 
    }
    pair<Poly, Poly> Divide(const Poly &a, const Poly &b) {
        int n = len(a), m = len(b); 
        Poly t1(a.rbegin(), a.rbegin() + n - m + 1), t2(b.rbegin(), b.rend()); 
        t2.resize(n - m + 1);
        Poly Q = Inv(t2) * t1; Q.resize(n - m + 1); 
        reverse(Q.begin(), Q.end());
        Poly R = Q * b; R.resize(m - 1); 
        for (int i = 0; i < len(R); ++i) 
            R[i] = add(a[i], p - R[i]);
        return make_pair(Q, R); 
    }
    Poly Ln(const Poly &a) {
        Poly res = Int(Der(a) * Inv(a));
        res.resize(len(a)); return res;
    }
    Poly Exp(const Poly &a) {
        Poly res(1, 1);
        int n = 1; while (n < len(a)) n <<= 1;
        for (int k = 2; k <= n; k <<= 1) {
            Poly t(res.begin(), res.end()); 
            t.resize(k); 
            t = Ln(t);
            for (int i = 0; i < min(len(a), k); ++i) 
                t[i] = add(a[i], p - t[i]); 
            t[0] = add(t[0], 1);
            res = res * t; res.resize(k);
        } res.resize(len(a)); return res;
    }
    Poly Sqrt(const Poly &a) { // a[0] = 1
        Poly res(1, 1); ll inv2 = pow_mod(2, p - 2); 
        int n = 1; while (n < len(a)) n <<= 1;
        for (int k = 2; k <= n; k <<= 1) {
            Poly t(res.begin(), res.end()), ta(a.begin(), a.begin() + min(len(a), k));
            t.resize(k); t = Inv(t) * ta; 
            res.resize(k); for (int i = 0; i < k; ++i) res[i] = mul(add(res[i], t[i]), inv2);
        } res.resize(len(a)); return res;
    }
    Poly Pow(const Poly &a, int k) { // a[0] = 1
        return Exp(Ln(a) * k);
    }
    Poly Pow(const Poly &a, int k, int kk) { 
        int n = len(a), t = n, m, v, inv, powv; Poly res(n);
        for (int i = n - 1; ~i; --i) if (a[i]) t = i, v = a[i];
        if (k && t >= (n + k - 1) / k) return res;
        if (t == n) { if (!k) res[0] = 1; return res; }
        m = n - t * k; res.resize(m);
        inv = pow_mod(v, p - 2); powv = pow_mod(v, kk); 
        for (int i = 0; i < m; ++i) res[i] = mul(a[i + (k > 0) * t], inv);
        res = Exp(Ln(res) * k); res.resize(n); 
        for (int i = m - 1; ~i; --i) {
            int tmp = mul(res[i], powv);
            res[i] = 0, res[i + t * k] = tmp;
        }
        return res;
    }
}  // namespace Pol
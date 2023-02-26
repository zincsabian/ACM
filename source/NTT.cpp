#include<bits/stdc++.h>
namespace polybase {
    constexpr int mod(998244353), G(3), L(1 << 20);
 
    inline void inc(int &x, int y)
    {
        x += y;
        if (x >= mod) x -= mod;
        if (x < 0) x += mod;
    }
 
    inline void dec(int &x, int y)
    {
        x -= y;
        if (x < 0) x += mod;
        if (x >= mod) x -= mod;
    }
 
    int fpow(int x, int k = mod - 2)
    {
        int r = 1;
        for (; k; k >>= 1, x = 1LL * x * x % mod)
        {
            if (k & 1) r = 1LL * r * x % mod;
        }
        return r;
    }
 
    int w[L], _ = []
    {
        w[L / 2] = 1;
        for (int i = L / 2 + 1, 
            x = fpow(G, (mod - 1) / L); i < L; i++) 
            w[i] = 1LL * w[i - 1] * x % mod;
        for (int i = L / 2 - 1; i >= 0; i--) 
            w[i] = w[i << 1];
        return 0;
    }();
 
    void dft(int *a, int n)
    {
        assert((n & n - 1) == 0);
        for (int k = n >> 1; k; k >>= 1)
        {
            for (int i = 0; i < n; i += k << 1)
            {
                for (int j = 0; j < k; j++)
                {
                    int &x = a[i + j], y = a[i + j + k];
                    a[i + j + k] = 1LL * 
                        (x - y + mod) * w[k + j] % mod;
                    inc(x, y);
                }
            }
        }
    }
 
    void idft(int *a, int n)
    {
        assert((n & n - 1) == 0);
        for (int k = 1; k < n; k <<= 1)
        {
            for (int i = 0; i < n; i += k << 1)
            {
                for (int j = 0; j < k; j++)
                {
                    int x = a[i + j], y = 1LL * 
                        a[i + j + k] * w[k + j] % mod;
                    a[i + j + k] = 
                        x - y < 0 ? x - y + mod : x - y;
                    inc(a[i + j], y);
                }
            }
        }
        for (int i = 0, inv = 
            mod - (mod - 1) / n; i < n; i++)
            a[i] = 1LL * a[i] * inv % mod;
        std::reverse(a + 1, a + n);
    }
 
    inline int norm(int n) { return 1 << std::__lg(n * 2 - 1); }
 
    struct poly : public std::vector<int>
    {
        #define T (*this)
        using std::vector<int>::vector;
 
        void append(const poly &r)
        {
            insert(end(), r.begin(), r.end());
        }
 
        int len() const { return size(); }
 
        poly operator-() const
        {
            poly r(T);
            for (auto &x : r) x = x ? mod - x : 0;
            return r;
        }
 
        poly &operator+=(const poly &r)
        {
            if (r.len() > len()) resize(r.len());
            for (int i = 0; i < r.len(); i++) inc(T[i], r[i]);
            return T;
        }
 
        poly &operator-=(const poly &r)
        {
            if (r.len() > len()) resize(r.len());
            for (int i = 0; i < r.len(); i++) dec(T[i], r[i]);
            return T;
        }
 
        poly &operator^=(const poly &r)
        {
            if (r.len() < len()) resize(r.len());
            for (int i = 0; i < len(); i++) 
                T[i] = 1LL * T[i] * r[i] % mod;
            return T;
        }
 
        poly &operator*=(int r)
        {
            for (int &x : T) x = 1LL * x * r % mod;
            return T;
        }
 
        poly operator+(const poly &r) const { return poly(T) += r; }
 
        poly operator-(const poly &r) const { return poly(T) -= r; }
 
        poly operator^(const poly &r) const { return poly(T) ^= r; }
 
        poly operator*(int r) const { return poly(T) *= r; }
 
        poly &operator<<=(int k) { return insert(begin(), k, 0), T; }
 
        poly operator<<(int r) const { return poly(T) <<= r; }
 
        poly operator>>(int r) const { 
            return r >= len() ? poly() : poly(begin() + r, end()); }
 
        poly &operator>>=(int r) { return T = T >> r; }
 
        poly pre(int k) const { 
            return k < len() ? poly(begin(), begin() + k) : T; }
 
        friend void dft(poly &a) { dft(a.data(), a.len()); }
 
        friend void idft(poly &a) { idft(a.data(), a.len()); }
 
        friend poly conv(const poly &a, const poly &b, int n)
        {
            poly p(a), q;
            p.resize(n), dft(p);
            p ^= &a == &b ? p : (q = b, q.resize(n), dft(q), q);
            idft(p);
            return p;
        }
 
        friend poly operator*(const poly &a, const poly &b)
        {
            int len = a.len() + b.len() - 1;
            if (a.len() <= 16 || b.len() <= 16)
            {
                poly c(len);
                for (int i = 0; i < a.len(); i++)
                    for (int j = 0; j < b.len(); j++)
                        c[i + j] = (c[i + j] 
                            + 1LL * a[i] * b[j] % mod) % mod;
                return c;
            }
            return conv(a, b, norm(len)).pre(len);
        }
 
        poly deriv() const
        {
            if (empty()) return poly();
            poly r(len() - 1);
            for (int i = 1; i < len(); i++) 
                r[i - 1] = 1LL * i * T[i] % mod;
            return r;
        }
 
        poly integ() const
        {
            if (empty()) return poly();
            poly r(len() + 1);
            for (int i = 0; i < len(); i++) 
                r[i + 1] = 1LL * fpow(i + 1) * T[i] % mod;
            return r;
        }
 
        poly inv(int m) const
        {
            poly x = {fpow(T[0])};
            for (int k = 1; k < m; k *= 2)
            {
                x.append(-((conv(pre(k * 2), 
                    x, k * 2) >> k) * x).pre(k));
            }
            return x.pre(m);
        }
 
        poly log(int m) const { return (deriv() 
            * inv(m)).integ().pre(m); }
 
        poly exp(int m) const
        {
            poly x = {1};
            for (int k = 1; k < m; k *= 2)
            {
                x.append((x * (pre(k * 2) - 
                    x.log(k * 2) >> k)).pre(k));
            }
            return x.pre(m);
        }
 
        poly sqrt(int m) const
        {
            poly x = {1}, y = {1};
            for (int k = 1; k < m; k *= 2)
            {
                x.append(((pre(k * 2) 
                    - x * x >> k) * y).pre(k) * (mod + 1 >> 1));
                if (k * 2 < m)
                {
                    y.append(-((conv(x.pre(k * 2), 
                        y, k * 2) >> k) * y).pre(k));
                }
            }
            return x.pre(m);
        }
 
        poly rev() const { return poly(rbegin(), rend()); }
 
        poly mulT(poly b) { return T * b.rev() >> b.len() - 1; }
 
#undef T
    };
}
int main(){
	
} 

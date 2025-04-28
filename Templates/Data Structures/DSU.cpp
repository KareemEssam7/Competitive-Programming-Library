template<typename t>
struct DSU {
    int n;
    vector<t> par, sz;
    DSU(int sz) {
        this->n = sz + 1;
        par = vector<t>(n);
        sz = vector<t>(n, 1);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    t find(t u) {
        return (par[u] == u ? u : par[u] = find(par[u]));
    }

    bool Union(t u, t v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) par[u] = v, sz[v] += sz[u];
        else par[v] = u, sz[u] += sz[v];
        return true;
    }
};
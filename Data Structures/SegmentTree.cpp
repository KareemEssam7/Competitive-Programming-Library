template<typename t>
struct SegTree {

public:

    SegTree(int n)
    {
        this->sz = n;
        int cur = 1;
        while (sz <= n) cur <<= 1;
        cur <<= 1;
        T.resize(cur);
    }

    void build(vector<t>&v) {
        build(1 , 0 , sz - 1 , v);
    }

    void update(int idx , t val) {
        update(1 , 0 , sz - 1 , idx , val);
    }

    t query(int l , int r) {
        return queryRange(1 , 0 , sz - 1 , l , r).sum;
    }

private:
    struct Node {
        t sum = 0;
    };
    
    int sz = 1;
    vector<Node>T;

    Node Merge(const Node &a , const Node &b) {
        Node ret;
        ret.sum = a.sum + b.sum;
        return ret;
    }

    Node Neutral = Node();

    Node Single(t val) {
        return {val};
    }

    void pull(int node) {
        T[node] = Merge(T[node << 1] , T[node << 1 | 1]);
    }

    void build(int node , int lx , int rx , vector<t>&v) {
        if (lx == rx)
            return T[node] = Single(v[lx]) , void();
        int mid = (lx + rx) >> 1;
        build(node << 1 , lx , mid , v);
        build(node << 1 | 1 , mid + 1 , rx , v);
        pull(node);
    }

    void update(int node , int lx , int rx , int idx , t val) {
        if (lx == rx)
            return T[node] = Single(val) , void();
        int mid = (lx + rx) >> 1;
        if (idx <= mid)
            update(node << 1 , lx , mid , idx , val);
        else
            update(node << 1 | 1 , mid + 1 , rx , idx , val);
        pull(node);
    }

    Node queryRange(int node , int lx , int rx , int l , int r) {
        if (l > rx or lx > r) return Neutral;
        if (lx >= l and rx <= r) return T[node];
        int mid = (lx + rx) >> 1;
        return Merge(queryRange(node << 1 , lx , mid , l , r) , queryRange(node << 1 | 1 , mid + 1 , rx , l , r));
    }
};
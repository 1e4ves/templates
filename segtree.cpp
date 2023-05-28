#define mid  ((l + r) >> 1)
template<class T>
struct SegTree {
    T tr[N << 2];

    void update(int u) {
        tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }

    void build(int u = 1, int l = 1, int r = n) {
        if (l == r) {
            //chanege this
            //---------

            //---------
            return;
        }
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        update(u);
    }
    void modify(int x, T v, int u = 1, int l = 1, int r = n) {
        if (l == r) {
            //change this
            //caution this '+' meaning
            //
            tr[u] = tr[u] + v;
            //----------------
            return;
        }
        if (x <= mid) modify(x, v, u << 1, l, mid);
        else modify(x, v, u << 1 | 1, mid + 1, r);
        update(u);
    }

    T query(int ql, int qr, int u = 1, int l = 1, int r = n) {
        if (ql > qr) {
            T t;
            return t;
        }
        if (ql <= l && r <= qr) {
            return tr[u];
        }
        if (qr <= mid) return query(ql, qr, u << 1, l, mid);
        else if(ql > mid) return query(ql, qr, u << 1 | 1, mid + 1, r);
        else return query(ql, qr, u << 1, l, mid) + query(ql, qr, u << 1 | 1, mid + 1, r);
    }
};

//修改inf
const int inf = 1 << 29;
struct Min {
    int x;

    Min(int x = inf) : x(x) {}

    Min operator+ (Min a){
        Min t;
        t.x = min(x, a.x);
        return t;
    }
};
struct Max {
    int x;

    Max(int x= -inf) : x(x) {}

    Max operator+ (Max a) {
        Max t;
        t.x = max(x, a.x);
        return t;
    }
};
#define mid  ((l + r) >> 1)
template<class Info, class Tag>
struct SegTree {
    Info tr[N << 2];
    Tag tag[N << 2];

    void update(int u) {
        tr[u] = tr[u << 1] + tr[u << 1 | 1];
    }

    void apply(int u, const Tag &v) {
        tr[u].apply(v);
        tag[u].apply(v);
    }
    void pushdown(int u) {
        apply(u << 1, tag[u]);
        apply(u << 1 | 1, tag[u]);
        tag[u] = Tag();
    }
    void build(int u = 1, int l = 1, int r = n) {
        if (l == r) {
            //重写
            //-----------
            tr[u] = {1, a[l]};


            //------------
            return;
        }
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        update(u);
    }

    void modify(int ql, int qr, const Tag &v, int u = 1 ,int l = 1, int r = n) {
        if (ql > qr) {
            return;
        }
        if (ql <= l && r <= qr) {
            apply(u, v);
            return;
        }

        pushdown(u);
        if (ql <= mid) modify(ql, qr, v, u << 1, l, mid);
        if (qr > mid) modify(ql, qr, v, u << 1 | 1, mid + 1, r);

        update(u);
    }

    Info query(int ql, int qr, int u = 1, int l = 1, int r = n) {
        if (ql > qr) {
            return Info();
        }
        if (ql <= l && r <= qr) {
            return tr[u];
        }

        pushdown(u);

        if (qr <= mid) return query(ql, qr, u << 1, l, mid);
        else if(ql > mid) return query(ql, qr, u << 1 | 1, mid + 1, r);
        else return query(ql, qr, u << 1, l, mid) + query(ql, qr, u << 1 | 1, mid + 1, r);
    }
};


//需要重写的东西
//(1) 区间乘区间加区间赋值， 查询区间和

//using Z = ll;
struct Tag {
    Z mul, add;
    Tag(Z mul = 1, Z add = 0) : mul(mul), add(add){}
    void apply(Tag t) {
        mul *= t.mul;
        add *= t.mul;
        add += t.add;
    }
};

struct Info {
    int len;
    Z sum;
    Info(int len = 1, Z sum = 0) : len(len), sum(sum) {}
    void apply(Tag t) {
        sum = sum * t.mul + t.add * len;
    }
};

Info operator+ (Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    return c;
}
//


// (2)区间赋值，查询历史和

struct Tag {
    ll a;
    ll al;
    int x;
    Tag(int a = 0, ll al = 0, ll x = -1) : a(a), al(al), x(x){}
//
    void apply (Tag t) {
        if (x == -1) {
            a += t.a;
        } else {
            al += t.a * x;
        }

        al += t.al;
        if (t.x != -1) {
            x = t.x;
        }
    }
};

struct Info {
    int len;
    ll sum;
    ll hsum;

    Info(int len = 0, ll sum = 0, ll hsum = 0) : len(len), sum(sum), hsum(hsum){}
    void apply(Tag t) {
        hsum += sum * t.a;
        hsum += len * t.al;
        if (t.x != -1) {
            sum = 1ll * t.x * len;
        }
    }
};

Info operator+ (Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.hsum = a.hsum + b.hsum;
    return c;
}
// 

// 

//(3) 区间加， 查询区间历史和
//

// using Z = ll;

struct Tag {
    Z add, hadd;
    int tim;
    Tag(Z add = 0, Z hadd = 0, int tim = 0) : add(add), hadd(hadd), tim(tim){}
    void apply(Tag t) {
        hadd += add * t.tim + t.hadd;
        add += t.add;
        tim += t.tim;
    }
};

struct Info {
    int len;
    Z sum;
    Z hsum;

    Info(int len = 1, Z sum = 0, Z hsum = 0) : len(len), sum(sum), hsum(hsum){}
    void apply(Tag t) {
       hsum += sum * t.tim + t.hadd * len;
       sum += t.add * len;
    }
};

Info operator+ (Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.hsum = a.hsum + b.hsum;
    return c;
}


SegTree<Info, Tag> seg;
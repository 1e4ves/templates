const ll N = 1e6 + 5;
const ll MOD = 998244353;
//const ll INF = 0x7fffffff;
const ll INF = 1e9 + 5;
#define lc x<<1
#define rc x<<1|1
struct node {
    int max, nax, cat;
    int min, nin, cit;
    int add;
    ll sum;
}t[N << 2];
int w[N];

inline void push_add(int x, int k, int len) {
    t[x].add += k;
    t[x].sum = t[x].sum + 1ll * k * len;
    t[x].max += k;
    t[x].nax += k;
    t[x].min += k;
    t[x].nin += k;
}
inline void push_min(int x, int k) {
    t[x].sum = t[x].sum - 1ll * (t[x].max - k) * t[x].cat;
    if (t[x].max == t[x].min)t[x].max = t[x].min = k;
    else if (t[x].max == t[x].nin)t[x].max = t[x].nin = k;
    else t[x].max = k;
}
inline void push_max(int x, int k) {
    t[x].sum = t[x].sum + 1ll * (k - t[x].min) * t[x].cit;
    if (t[x].min == t[x].max)t[x].min = t[x].max = k;
    else if (t[x].min == t[x].nax)t[x].min = t[x].nax = k;
    else t[x].min = k;
}
inline void pushdown(int x, int l, int r) {
    int mid = (l + r) >> 1;
    if (t[x].add) {
        push_add(lc, t[x].add, mid - l + 1);
        push_add(rc, t[x].add, r - mid);
        t[x].add = 0;
    }
    if (t[x].max < t[lc].max)push_min(lc, t[x].max);
    if (t[x].max < t[rc].max)push_min(rc, t[x].max);
    if (t[x].min > t[lc].min)push_max(lc, t[x].min);
    if (t[x].min > t[rc].min)push_max(rc, t[x].min);
}

inline void merge(int x) {
    t[x].sum = t[lc].sum + t[rc].sum;

    if (t[lc].max == t[rc].max) {
        t[x].max = t[lc].max;
        t[x].cat = t[lc].cat + t[rc].cat;
        t[x].nax = max(t[lc].nax, t[rc].nax);
    }
    else if (t[lc].max > t[rc].max) {
        t[x].max = t[lc].max;
        t[x].cat = t[lc].cat;
        t[x].nax = max(t[lc].nax, t[rc].max);
    }
    else {
        t[x].max = t[rc].max;
        t[x].cat = t[rc].cat;
        t[x].nax = max(t[rc].nax, t[lc].max);
    }

    if (t[lc].min == t[rc].min) {
        t[x].min = t[lc].min;
        t[x].cit = t[lc].cit + t[rc].cit;
        t[x].nin = min(t[lc].nin, t[rc].nin);
    }
    else if (t[lc].min < t[rc].min) {
        t[x].min = t[lc].min;
        t[x].cit = t[lc].cit;
        t[x].nin = min(t[lc].nin, t[rc].min);
    }
    else {
        t[x].min = t[rc].min;
        t[x].cit = t[rc].cit;
        t[x].nin = min(t[rc].nin, t[lc].min);
    }
}

void build(int x, int l, int r) {
    if (l == r) {
        t[x].sum = t[x].max = t[x].min = w[l];
        t[x].cat = t[x].cit = 1;
        t[x].nax = -INF;
        t[x].nin = INF;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    merge(x);
}

void modify_add(int x, int k, int l, int r, int L, int R) {
    if (l == L && r == R) {
        push_add(x, k, r - l + 1);
        return;
    }
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)modify_add(lc, k, l, r, L, mid);
    else if (l > mid)modify_add(rc, k, l, r, mid + 1, R);
    else modify_add(lc, k, l, mid, L, mid), modify_add(rc, k, mid + 1, r, mid + 1, R);
    merge(x);
}

void modify_min(int x, int k, int l, int r, int L, int R) {
    if (k >= t[x].max)return;
    if (l == L && r == R && k > t[x].nax) {
        push_min(x, k);
        return;
    }
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)modify_min(lc, k, l, r, L, mid);
    else if (l > mid)modify_min(rc, k, l, r, mid + 1, R);
    else modify_min(lc, k, l, mid, L, mid), modify_min(rc, k, mid + 1, r, mid + 1, R);
    merge(x);
}

void modify_max(int x, int k, int l, int r, int L, int R) {
    if (k <= t[x].min)return;
    if (l == L && r == R && k < t[x].nin) {
        push_max(x, k);
        return;
    }
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)modify_max(lc, k, l, r, L, mid);
    else if (l > mid)modify_max(rc, k, l, r, mid + 1, R);
    else modify_max(lc, k, l, mid, L, mid), modify_max(rc, k, mid + 1, r, mid + 1, R);
    merge(x);
}

ll query_sum(int x, int l, int r, int L, int R) {
    if (l == L && r == R)return t[x].sum;
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)return query_sum(lc, l, r, L, mid);
    else if (l > mid)return query_sum(rc, l, r, mid + 1, R);
    else return query_sum(lc, l, mid, L, mid) + query_sum(rc, mid + 1, r, mid + 1, R);
}

int query_max(int x, int l, int r, int L, int R) {
    if (l == L && r == R)return t[x].max;
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)return query_max(lc, l, r, L, mid);
    else if (l > mid)return query_max(rc, l, r, mid + 1, R);
    else return max(query_max(lc, l, mid, L, mid), query_max(rc, mid + 1, r, mid + 1, R));
}

int query_min(int x, int l, int r, int L, int R) {
    if (l == L && r == R)return t[x].min;
    pushdown(x, L, R);
    int mid = (L + R) >> 1;
    if (r <= mid)return query_min(lc, l, r, L, mid);
    else if (l > mid)return query_min(rc, l, r, mid + 1, R);
    else return min(query_min(lc, l, mid, L, mid), query_min(rc, mid + 1, r, mid + 1, R));
}
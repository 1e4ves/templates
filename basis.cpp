struct Basis {
    bitset<N> a[N], b[N];
    //n个m位数
    int n, m;
    void init(int n, int m) {
        this.n = n;
        this.m = m;
    }
    void insert(int i) {
        for (int j = m; j; j--) {
            if (a[i][j]) {
                if (!id[j]) {
                    ++rk;
                    id[j] = i;
                    pos[i] = j;
                    return;
                } else {
                    a[i] ^= a[id[j]];
                    b[i] ^= b[id[j]];
                }
            }
        }
        pos[i] = 0;
    }

    int erase(int i) {
        int mn = n + 1, x = 0;
        for (int j = 1; j <= p; j++) if (b[j][i] && chkmin(mn, pos[j])) x = j;
        for (int j = 1; j <= p; j++) if (b[j][i] && j != x) a[j] ^= a[x], b[j] ^= b[x];
        if (pos[x]) --rk, id[pos[x]] = x, pos[x] = 0;
        a[x].reset(); b[x].reset(); return x;
    }
}
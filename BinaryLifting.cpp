const int LOGN = 20;
int fa[N][LOGN + 1];
int dep[N], in[N], out[N], tot;
void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    in[u] = ++tot;
    fa[u][0] = p;

    for (int j = 1; j <= LOGN; j++) {
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }

    for (int v : e[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    out[u] = tot;

}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i <= LOGN; i++) if (d & (1 << i)) {
            u = fa[u][i];
        }
    if (u == v) return u;

    for (int i = LOGN; i >= 0; i--) if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}

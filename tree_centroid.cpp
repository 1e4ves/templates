void dfs(int u, int p) {
	sz[u] = 1;
	for (int v : e[u]) {
		if (v == p) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
}

int find_centroid(int u, int p, int s) {
	for (int v : e[u]) {
		if (v == p || sz[v] * 2 <= s) continue;
		return find_centroid(v, u, s);
	}
	return u;
}
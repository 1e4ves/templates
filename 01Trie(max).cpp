const int N = 100010;
const int LOGN = 30;

struct trie01 {
	int nex[N * LOGN][2], tot;
	int cnt[N * LOGN][2];
	//能写非递归肯定优先非递归

	//从高位到低位存储
	void insert(int x) {
		int u = 0;
		for(int i = LOGN; i >= 0; i--) {
			int c = (x >> i) & 1;
			if(!nex[u][c]) nex[u][c] = ++ tot;
			cnt[u][c] ++;
			u = nex[u][c];
		}
	}

	void del(int x) {
		int u = 0;
		for(int i = LOGN; i >= 0; i--) {
			int c = (x >> i) & 1;
			if(!nex[u][c]) return;
			cnt[u][c] --;
			u = nex[u][c];
		}
	}

	// 基于贪心查询与x的最大异或
	int query(int x) {
		int u = 0;
		int res = 0;
		for(int i = LOGN; i >= 0; i--) {
			int c = ((x >> i) & 1) ^ 1;
			if(nex[u][c]) {
				u = nex[u][c];
				res |= (1ll << i);
			}else {
				u = nex[u][c ^ 1];
			}
		}
		return res;
	}

	//x与多少数异或小于y
	int query(int x, int y) {
		int u = 0;
		int res = 0;
		for(int i = LOGN; i >= 0; i--) {
			int a = (x >> i) & 1;
			int b = (y >> i) & 1;

			if(b) {
				res += cnt[u][a];
				if(!cnt[u][a ^ 1]) break;
				else u = nex[u][a ^ 1];
			}else {
				if(!cnt[u][a]) break;
				else u = nex[u][a];
			}
		}
		return res;
	}
}tr;

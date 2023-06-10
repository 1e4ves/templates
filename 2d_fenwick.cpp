
//单点修改，查询子矩阵
template <typename T>
struct Fenwick {
    int n, m;
    vector<vector<T>> a;

    Fenwick(int n = 0, int m = 0) {
        init(n, m);
    }

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        a.assign(n + 1, vector(m + 1, T()));
    }

    void add(int x, int y, T v) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                a[i][j] += v;
            }
        }
    }
    T query(int x, int y) {
        assert(x >= 0 && y >= 0);
        if (x == 0 || y == 0) return T();
        T res = T();
        for (int i = x; i; i -= i & -i) {
            for (int j = y; j; j -= j & -j) {
                res += a[i][j];
            }
        }
        return res;
    }

    T query(int x1, int y1, int x2, int y2) {
        assert(x1 >= 1 && y1 >= 1);
        assert(x2 >= 1 && y2 >= 1);
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

};
//子矩阵修改
template <typename T>
struct Fenwick {
    int n, m;
    vector<vector<T>> a, b, c, d;

    Fenwick(int n = 0, int m = 0) {
        init(n, m);
    }

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        a.assign(n + 1, vector(m + 1, T()));
       	b.assign(n + 1, vector(m + 1, T()));
       	c.assign(n + 1, vector(m + 1, T()));
       	d.assign(n + 1, vector(m + 1, T()));
    }

   	void add(int x, int y, T z) {
   		for (int i = x; i <= n; i += i & -i) {
   			for (int j = y; j <= m; j += j & -j) {
   				a[i][j] += z;
   				b[i][j] += z * x;
   				c[i][j] += z * y;
   				d[i][j] += z * x * y;
   			}
   		}
   	}

   	void add(int x1, int y1, int x2, int y2, T z) {
   		add(x1, y1, z);
   		add(x1, y2 + 1, -z);
   		add(x2 + 1 ,y1, -z);
   		add(x2 + 1, y2 + 1, z);
   	}
    T query(int x, int y) {
    	assert(x >= 0 && y >= 0);
    	if (x == 0 || y == 0) return 0;
    	T res = T();
    	for (int i = x; i; i -= i & -i) {
    		for (int j = y; j; j -= j & -j) {
    			res += a[i][j] * (x + 1) * (y + 1) - b[i][j] * (y + 1)=
    					c[i][j] * (x + 1) + d[i][j];
    		}
    	}
    	return res;
    }

    T query(int x1, int y1, int x2, int y2) {
    	assert(x1 >= 1 && y1 >= 1);
    	assert(x2 >= 1 && y2 >= 1);
    	return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

};
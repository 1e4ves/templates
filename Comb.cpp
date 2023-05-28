namespace Comb {
	//using Z = ll;
	int _n = 0;
	vector<Z> _fac(1, 1);
	vector<Z> _invfac(1, 1);
	vector<Z> _inv(1, 0);

	void init(int m) {
        if (m <= _n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = _n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > _n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        _n = m;
    }

    Z fac(int m) {
        if (m > _n) init(2 * m);
        return _fac[m];
    }

    Z invfac(int m) {
        if (m > _n) init(2 * m);
        return _invfac[m];
    }

    Z inv(int m) {
        if (m > _n) init(2 * m);
        return _inv[m];
    }

    Z C(int n, int m) {
    	if (n < m || m < 0) return 0;
    	return fac(n) * invfac(m) * invfac(n - m);
    }
}

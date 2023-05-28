
vector<pair<ll, ll>> enum_quotient(ll n) {
	vector<pair<ll, ll>> res;
	ll l = 1;
	while(l <= n) {
		ll r = n / (n / l) + 1;
		res.emplace_back(l, r);
		l = r;
	}

	//O(1) 求所在区间左右端点：
	// int t = n / k
	// t <= n / k < t + 1
	// n / (t + 1) < k <= n / t
	// (n / (t + 1)) + 1 <= k <= n / t
	
	//[l, r)
	//按商递减的顺序来
	res.emplace_back(n + 1, n + 2);
	return res;
}

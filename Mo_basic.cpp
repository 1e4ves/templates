int B;
array<int, 3> queries[N];

B = n / sqrt(q);
if (B == 0) B++;

sort(queries+ 1, queries + 1 + q, [&](array<int, 3> a, array<int, 3> b){
    int t = a[0] / B;
    if(t != b[0] / B) return a[0] < b[0];
    return (t % 2) ? (a[1] > b[1]) : (a[1] < b[1]);
});


for (int i = 1; i <= q; i++) {
   while (r < queries[i][1]) add(++r);
   while (l > queries[i][0]) add(--l);
   while (r > queries[i][1]) del(r--);
   while (l < queries[i][0]) del(l++);

   ans[queries[i][2]] = res;
}

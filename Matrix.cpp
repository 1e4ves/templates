using T = Z;
using Mat = vector<vector<T>>;

Mat makeMat(int r, int c) {
    return Mat(r, vector<T>(c));
}
Mat makeId(int n) {
    Mat m = makeMat(n, n);
    for (int i = 0; i < n; i++) m[i][i] = 1;
    return m;
}
Mat& operator+= (Mat& a, const Mat& b){
    assert(a.size() == b.size() && a[0].size() == b[0].size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            a[i][j] += b[i][j];
        }
    }
    return a;
}
Mat& operator-= (Mat& a, const Mat& b){
    assert(a.size() == b.size() && a[0].size() == b[0].size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            a[i][j] -= b[i][j];
        }
    }
    return a;
}
Mat operator*(const Mat& a, const Mat& b) {
    int x = a.size(), y = a[0].size(), z = b[0].size();
    assert(y == b.size());
    Mat c = makeMat(x, z);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                c[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return c;
}
Mat operator+(Mat a, const Mat& b){return a += b;}
Mat operator-(Mat a, const Mat& b){return a -= b;}
Mat& operator*= (Mat& a, const Mat& b) {return a = a * b;}
Mat pow(Mat m, ll p) {
    int n = m.size();
    assert(n == m[0].size() && p >= 0);
    Mat res = makeId(n);
    for(; p; p /= 2, m *= m) if (p & 1) res *= m;
    return res;
}
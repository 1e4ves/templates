struct trie {
    //[0] 编号
    //[1] 以此为前缀的字符串的个数
    int nex[N][26][2], tot;
    void insert(string s, int l) {
        int u = 0;
        for(int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            
            if(!nex[u][c][0]) nex[u][c][0] = ++tot;
            nex[u][c][1] ++;

            u = nex[u][c][0];
        }
    }
}tr;
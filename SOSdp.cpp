    for (int i = 1; i < (1 << z1); i *= 2) {
        for (int j = 0; j < (1 << z1); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                //a[j + k] 为 a[i + j + k] 的子集
                chkmin(a[j + k], a[i + j + k]);
            }
        }
    }

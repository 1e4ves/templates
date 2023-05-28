int a[N], l[N], r[N];

void build() {
    stack<int> st;
    int root = 0;
    //clear
    for(int i = 1; i <= n; i++) l[i] = r[i] = 0;

    for(int i = 1; i <= n; i++) {
        int last = 0;
        while(!st.empty() && a[st.top()] < a[i]) {
            last = st.top();
            st.pop();
        }
        if(!st.empty()) r[st.top()] = i;
        else root = i;
        l[i] = last;
        st.push(i);
    }

    //do tree dp or sth 
    
}
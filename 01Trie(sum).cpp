const int N = 100010;
const int LOGN = 21;
int tot;
struct node{
	int w, v, ch[2];
}tr[N * M];

void update(int u) {
	tr[u].v = tr[u].w = 0;
	int x = tr[u].ch[0], y = tr[u].ch[1];

	if(x && tr[x].w) tr[x].w ^= 1;
	if(y && tr[y].w) tr[y].w ^= 1;

	if(x) {
		tr[u].v ^= (tr[x].v << 1);
	} 

	if(y) {
		tr[u].v ^= ((tr[y].v << 1) | tr[y].w);
	}
}

void insert(int& u, int x, int dep) {
	if(!u) u = ++ tot;
	if(dep >= LOGN) {
		tr[u].w ^= 1;
		return;
	}
	insert(tr[u].ch[x & 1], (x >> 1), dep + 1);
	update(u);
}
//需要注意，如果不满足删除一定合法，w必须搞成
//实际数量，不能是%2
//而如果满足删除一定合法，那么del可以被insert代替
// void del(int& u, int x, int dep) {
// 	if(! u) u = ++ tot;
// 	if(dep >= LOGN) {
// 		tr[u].w --;
// 		return;
// 	}

// 	del(tr[u].ch[x & 1], (x >> 1), dep + 1);
// 	update(u);
// }


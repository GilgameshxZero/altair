const int maxn = 300005;
int tot, n, unionfa[maxn], sz[maxn], ch[maxn][2], fa[maxn];
int getfa(int x){ return unionfa[x] == x ? x : unionfa[x] = getfa(unionfa[x]); }
int upd(int x){
    sz[0] = 0;
    if (x)  sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}
int ro(int x){
    int y = fa[x], d = ch[y][1] == x;
    ch[y][d] = ch[x][!d], ch[x][!d] = y;
    if (fa[y]) ch[fa[y]][ ch[fa[y]][1] == y ] = x;
    fa[ch[y][d]] = y, fa[x] = fa[y], fa[y] = x;
    upd(y);
}
int splay(int x, int gf = 0){
    int y = 0;
    while ((y = fa[x]) != gf){
        if (fa[y] != gf)
            if ((ch[y][0] == x) ^ (ch[fa[y]][0] == y)) ro(x); else ro(y);
        ro(x);
    }upd(x);
}
/*
 * Specifies the integer N.
 */
void init(int N) {
    n = N;
     tot = 2 * n;
     for (int i = 1; i <= n; i ++){
         ch[i][0] = 0, ch[i][1] = i + n, sz[i] = 2;
         ch[i + n][0] = ch[i + n][1] = 0, sz[i + n] = 1;
         fa[i + n] = i, fa[i] = 0;
     }
     for (int i = 1; i <= n; i ++) unionfa[i] = i;
}

/*
 * Make A the parent of B.
 */
void make_parent(int A, int B) {
    int a = A, b= B;
     splay(a);
     int nxt = ch[a][1];
     while (ch[nxt][0]) nxt = ch[nxt][0];
     splay(nxt, a);
     
     splay(b);
     ch[nxt][0] = b;
     fa[b] = nxt;
     upd(nxt), upd(a);
     
     a = getfa(a), b = getfa(b);
     unionfa[a] = b;
}

/*
 * Return true if A is an ancestor of B.
 */
bool is_ancestor(int A, int B) {
  int a = A, b= B;
       if (getfa(a) !=  getfa(b)) return false;
    splay(a);
    int l = ch[a][0] ? sz[ch[a][0]] + 1 : 1;
    splay(a + n);
    int r = ch[a+n][0] ? sz[ch[a+n][0]] + 1 : 1;
    splay(b);
    int at = ch[b][0] ? sz[ch[b][0]] + 1 : 1;
    if (at >= l && at < r) return true;
    return false;
}

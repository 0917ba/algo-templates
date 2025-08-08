struct HLD{
    static const int MAX = N;
    int cnt, s[MAX], in[MAX], out[MAX], top[MAX], dep[MAX], par[MAX];
    vi adj[MAX];

    void init(int m = MAX-1){
        cnt = 0;
        fors(i, 0, m){
            s[i]=in[i]=out[i]=top[i]=dep[i]=par[i]=0;
            adj[i].clear();
        }
    }
    void build(int root = 1){ hld(root); ett(root); }
    void add_edge(int a, int b) { adj[a].push_back(b); adj[b].push_back(a); }

    void hld(int x, int p = -1) {
        s[x] = 1;
        forr(i, sz(adj[x])){
            int nxt = adj[x][i];
            if(nxt == p){
                adj[x].erase(adj[x].begin() + i);
                break;
            }
        }
        for(auto& i:adj[x]){
            dep[i] = dep[x] + 1; par[i] = x;
            hld(i, x);
            s[x] += s[i];
            if(s[adj[x][0]] < s[i]) swap(adj[x][0], i);
        }
    }
    void ett(int x){
        in[x] = ++cnt;
        for(int i:adj[x]){
            top[i] = (adj[x][0] == i) ? top[x] : i;
            ett(i);
        }
        out[x] = cnt;
    }
    // Path query from a to b
    int query(int a, int b){
        int ret = 0;
        while(top[a] != top[b]){
            if(dep[top[a]] > dep[top[b]]) swap(a, b);
            // Query from in[top[b]] to in[b]
            b = par[top[b]];
        }
        if(dep[a] > dep[b]) swap(a, b);
        // Query from in[a] to in[b]
        // If edge query, query at [in[a]+1, in[b]]
        return ret;
    }
    // Subtree query
    int query(int root){
        int ret = 0;
        // Query from in[root] to out[root]
        return ret;
    }
    int lca(int a, int b){
        while(top[a] != top[b]){
            if(dep[top[a]] > dep[top[b]]) swap(a, b);
            b = par[top[b]];
        }
        return dep[a] < dep[b] ? a : b;
    }
} hld;
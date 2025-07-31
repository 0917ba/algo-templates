struct Dinic{
    static const int MAX = N;
    int S=-1, E=-1, lv[MAX], c[MAX][MAX], f[MAX][MAX], last[MAX];
    vi adj[MAX];

    void init(int lim = MAX-1){
        S=E=-1;
        fors(i, 0, lim){
            adj[i].clear();
            lv[i]=last[i]=0;
            fors(j, 0, lim) c[i][j]=f[i][j]=0;
        }
    }
    void add_edge(int u, int v, int cc){
        adj[u].push_back(v);
        adj[v].push_back(u);
        c[u][v]=cc;
    }
    bool bfs(){
        mset(lv, -1);
        lv[S] = 0;
        queue<int> q;
        q.push(S);

        while(sz(q)){
            int x = q.front(); q.pop();
            for(int i:adj[x]){
                if(lv[i]!=-1 || c[x][i]-f[x][i]==0) continue;
                lv[i] = lv[x]+1;
                q.push(i);
            }
        }
        return lv[E]!=-1;
    }
    int dfs(int x, int flow){
        if(x==E) return flow;
        for(int j=last[x]; j<sz(adj[x]); j++){
            int i = adj[x][j];
            last[x] = j;

            if(c[x][i]-f[x][i]>0 && lv[i]==lv[x]+1){
                int nf = dfs(i, min(flow, c[x][i]-f[x][i]));
                if(nf>0){
                    f[x][i] += nf;
                    f[i][x] -= nf;
                    return nf;
                }
            }
        }
        return 0;
    }
    int maxflow(){
        assert(S!=-1 && E!=-1);
        int flow = 0;
        while(bfs()){
            mset(last, 0);

            while(1){
                int x = dfs(S, inf);
                if(x==0) break;
                flow += x;
            }
        }
        return flow;
    }
} net;
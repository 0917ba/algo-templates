struct MCMF{
    static const int MAX = 808;
    struct edge { int v, r, c, d; };

    vector<edge> g[MAX];
    int dist[MAX], prv[MAX], pidx[MAX];
    bool inq[MAX];

    void init(int n = MAX-1){
        forr(i, n){
            dist[i] = prv[i] = pidx[i] = inq[i] = 0;
            g[i].clear();
        }
    }
    void add_edge(int u, int v, int c, int d){
        g[u].push_back({v, sz(g[v]), c, d});
        g[v].push_back({u, sz(g[u])-1, 0, -d});
    }
    bool augment(int s, int t){
        fill(inq, inq+MAX, 0); fill(dist, dist+MAX, inf);
        queue<int> q;
        q.push(s); dist[s] = 0; inq[s] = 1;

        while(sz(q)){
            int x = q.front(); q.pop(); inq[x] = 0;
            forr(i, sz(g[x])){
                auto&[y, z, c, d] = g[x][i];
                if(c>0 && dist[y]>dist[x]+d){
                    dist[y] = dist[x]+d;
                    prv[y] = x; pidx[y] = i;
                    if(!inq[y]) q.push(y), inq[y] = 1;
                }
            }
        }
        return dist[t] < inf;
    }
    // flow, cost
    pi minimum_cost_flow(int s, int t){
        int flow=0, cost=0;
        while(augment(s, t)){
            int path = inf;
            for(int i=t; i!=s; i=prv[i]){
                auto& e = g[prv[i]][pidx[i]];
                path = min(path, e.c);
            }
            flow += path; cost += path * dist[t];
            for(int i=t; i!=s; i=prv[i]){
                auto& e = g[prv[i]][pidx[i]];
                e.c -= path; g[i][e.r].c += path;
            }
        }
        return {flow, cost};
    }
} net;

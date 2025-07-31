// 1-Based
struct UndirectedEulerGraph{
    static const int MAX_V = N, MAX_E = N;
    int num_v, num_e, edge_cnt;
    int deg[MAX_V], now[MAX_V], vis[MAX_E];
    vpi adj[MAX_V];
    vi vord, eord;
  
    void init(int max_v = MAX_V-1, int max_e = MAX_E-1){
        vord.clear(); eord.clear();
        num_v = max_v; num_e = max_e; edge_cnt = 0;
        fill(vis, vis+max_e+1, 0);
        fors(i, 1, max_v){
            deg[i]=now[i]=0;
            adj[i].clear();
        }
    }
    void add_edge(int u, int v){
        deg[v]++; deg[u]++;
        adj[u].emplace_back(v, ++edge_cnt); 
        adj[v].emplace_back(u, edge_cnt);
    }
    void pop_edge(int u, int v){
        deg[v]--; deg[u]--;
        adj[u].pop_back(); adj[v].pop_back();
        edge_cnt--;
    }
    void dfs(int x){
        while(now[x] < sz(adj[x])){
            auto[y, p] = adj[x][now[x]++];
            if(vis[p]) continue;
            vis[p] = 1; dfs(y);
            eord.push_back(p);
        }
        vord.push_back(x);
    }
    bool find_circuit(){
        vord.clear(); eord.clear();
        // If no edges
        if(edge_cnt==0) return vord.push_back(1), 1;
        fors(i, 1, num_v) if(deg[i]&1) return 0;
    
        fors(i, 1, num_v){
            if(deg[i]>0){
                dfs(i); 
                break;
            }
        }
        return sz(eord) == edge_cnt;
    }
    bool find_trail(){
        vord.clear();
        eord.clear();
        int S=-1, E=-1;
        fors(i, 1, num_v) if(deg[i]&1){
            if(S==-1) S=i;
            else if(E==-1) E=i;
            else return 0;
        }
        if(S==-1) return find_circuit();
        if(S!=-1 && E==-1) return 0;
      
        add_edge(S, E);
        dfs(S);
        forr(i, sz(eord)){
            if(eord[i] == edge_cnt){
                fors(j, 1, i) vord.push_back(vord[j]);
                vord.erase(vord.begin(), vord.begin()+i+1);
                fors(j, 0, i-1) eord.push_back(eord[j]);
                eord.erase(eord.begin(), eord.begin()+i+1);
                break;
            }
        }
        pop_edge(S, E);
        return sz(eord) == edge_cnt;
    }
} eu;
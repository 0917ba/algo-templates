// 1-Based
struct DirectedEulerGraph{
    static const int MAX_V = N, MAX_E = N;
    int num_v, num_e, edge_cnt;
    int in[MAX_V], out[MAX_V], now[MAX_V], vis[MAX_E];
    vpi adj[MAX_V];
    vi vord, eord;
  
    void init(int max_v = MAX_V-1, int max_e = MAX_E-1){
        vord.clear(); eord.clear();
        num_v = max_v; num_e = max_e; edge_cnt = 0;
        fill(vis, vis+max_e+1, 0);
        fors(i, 1, max_v){
            in[i]=out[i]=now[i]=0;
            adj[i].clear();
        }
    }
    void add_edge(int u, int v){
        in[v]++; out[u]++;
        adj[u].emplace_back(v, ++edge_cnt);
    }
    void pop_edge(int u, int v){
        in[v]--; out[u]--;
        adj[u].pop_back();
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
        fors(i, 1, num_v) if(in[i]!=out[i]) return 0;
    
        fors(i, 1, num_v) if(out[i]>0) {
            dfs(i); break;
        }
        reverse(all(vord)); reverse(all(eord));
        return sz(eord) == edge_cnt;
    }
    bool find_trail(){
        vord.clear();
        eord.clear();
        int S=-1, E=-1;
        fors(i, 1, num_v){
            if(in[i]==out[i]) continue;
            else if(out[i]==in[i]+1) { if(S==-1) S=i; else return 0; }
            else if(in[i]==out[i]+1) { if(E==-1) E=i; else return 0; }
            else return 0;
        }
        if(S==-1 && E==-1) return find_circuit();
        if(S==-1 || E==-1) return 0;
      
        add_edge(E, S);
        dfs(S);
        reverse(all(vord)); reverse(all(eord));
      
        forr(i, sz(eord)){
            if(eord[i] == edge_cnt){
                fors(j, 1, i) vord.push_back(vord[j]);
                vord.erase(vord.begin(), vord.begin()+i+1);
                fors(j, 0, i-1) eord.push_back(eord[j]);
                eord.erase(eord.begin(), eord.begin()+i+1);
                break;
            }
        }
        pop_edge(E, S);
        return sz(eord) == edge_cnt;
    }
} eu;
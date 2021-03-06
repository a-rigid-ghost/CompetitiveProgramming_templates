////LCA
////up[i][0] means parent of i
////when up[i][j] goes above root it ends up at 0

struct LCA{
    vector<ve> adj,up;
    ve tin,tout,dep;
    lli n,maxj,timer=0;
    
    void dfs(lli root,lli par){
        tin[root]= ++timer;
        up[root][0]=par;
        fr(i,1,maxj+1){
            up[root][i]=up[up[root][i-1]][i-1];
        }
        for(auto e:adj[root]){
            if(e!=par){
                dep[e]=dep[root]+1;
                dfs(e,root);
            }
        }
        tout[root]= ++timer;
    }
    
    lli isanc(lli a,lli b){
        return (tin[a]<=tin[b] && tout[a]>=tout[b]);
    }
    
    LCA(lli n1,ve adj1[]){
        n=n1;
        maxj=log2(n)+2;
        adj.resize(n+1);
        tin.assign(n+1,-1);
        tout.assign(n+1,-1);
        up.assign(n+1,ve(maxj+1,0));
        dep.assign(n+1,0);
        fr(i,1,n+1) adj[i]=adj1[i];
        tin[0]=-INF,tout[0]=INF;
        dfs(1,0);
    }
    
    lli findlca(lli a,lli b){
        if(isanc(a,b)) return a;
        if(isanc(b,a)) return b;
        frx(i,maxj,-1){
            if(!isanc(up[a][i],b)){
                a=up[a][i];
            }
        }
        return up[a][0];
    }
    
    lli dist(lli a,lli b){
        lli c=findlca(a,b);
        return dep[a]+dep[b]-2*dep[c];
    }
    
    lli kanc(lli a,lli k){
        fr(i,0,maxj+1){
            if(k&(1LL<<i)){
                a=up[a][i];
            }
        }
        return a;
    }
};

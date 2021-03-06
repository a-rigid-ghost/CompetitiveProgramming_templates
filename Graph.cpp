//////BASIC GRAPH STRUCTURE

const lli N=1e5+10;
lli n,m;
ve adj[N],vis(N,0);

void graphInput(){
    cin>>n>>m;
    fr(i,0,n+5){
        adj[i].clear();
        vis[i]=0;
    }
    fr(i,0,m){
        lli u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

void dfs(lli root){
    vis[root]=1;
    for(auto e:adj[root]){
        if(!vis[e]){
            dfs(e);
        }
    }
}

void bfs(lli start){
    vis[start]=1;
    queue<lli> q;
    q.push(start);
    while(!q.empty()){
        lli cur=q.front();
        q.pop();
        for(auto e:adj[cur]){
            if(!vis[e]){
                vis[e]=1;
                q.push(e);
            }
        }
    }
}

/////Djikstra

const lli N=1e5+10;
lli n,m;
vector<ve> adj[N];
 
void graphInput(){
    cin>>n>>m;
    fr(i,0,n+5){
        adj[i].clear();
    }
    fr(i,0,m){
        lli u,v,w;
        cin>>u>>v>>w;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
}

ve Djikstra(lli x){
    ve dist(N,1e18);
    dist[x]=0;
    set<ve> s;
    fr(i,1,n+1)s.insert({dist[i],i});
    while(!s.empty()){
        auto cur=*s.begin();
        s.erase(s.begin());
        for(auto e:adj[cur[1]]){
            if(dist[e[0]]>dist[cur[1]]+e[1]){
                s.erase({dist[e[0]],e[0]});
                dist[e[0]]=dist[cur[1]]+e[1];
                s.insert({dist[e[0]],e[0]});
            }
        }
    }
    return dist;
}

/////GRID BFS 

lli n,m,w;
ve dr={1,-1,0,0};
ve dc={0,0,1,-1};

lli check(lli i,lli j){
    if(i>0 && i<=n && j>0 && j<=m)return 1;
    return 0;
}

vector<ve> bfs(lli x,lli y){
    vector<ve> dist(n+5,ve(m+5,-1));
    queue<pll> q;
    dist[x][y]=0;
    q.push(mp(x,y));
    while(!q.empty()){
        pll cur=q.front();
        q.pop();
        fr(i,0,4){
            lli r=cur.F+dr[i],c=cur.S+dc[i];
            if(check(r,c) && dist[r][c]==-1){
                dist[r][c]=dist[cur.F][cur.S]+1;
                q.push(mp(r,c));
            }
        }
    }
    return dist;
}

/////////////Tarjan

const lli N=1e5+5;
lli mod=1e9+7;
ve adj[N];
lli ids[N],low[N]={0},stacks[N]={0},visited[N]={0},id=0,n,m;
stack<lli> instack;

void tarjan(lli cur){
    ids[cur]=++id;
    low[cur]=id;
    visited[cur]=1;
    stacks[cur]=1;
    instack.push(cur);
    for(auto nei:adj[cur]){
        if(!visited[nei]) tarjan(nei);
        if(stacks[nei]) low[cur]=min(low[cur],low[nei]);
    }
    if(low[cur]==ids[cur]){
        while(1){
            lli con=instack.top();
            instack.pop();
            low[con]=low[cur];
            stacks[con]=0;
            if(con==cur)break;
        }
    }
}

////////////Diameter
lli dia=0;
lli dfs(lli root,lli par){
    ve v;
    for(auto chi:adj[root]){
        if(chi!=par){
            v.pb(dfs(chi,root));
        }
    }
    lli sz=v.size();
    if(sz==0)return 0;
    if(sz==1){
        dia=max(dia,v[0]+1);
        return v[0]+1;
    }
    sort(all(v),greater<lli>());
    dia=max(dia,2+v[0]+v[1]);
    return v[0]+1;
}

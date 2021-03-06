/////greedy sweepline implementation style
///// initial positions a[], cost to move per unit t[]
/////find min cost so that all are finally at distinct positions

void solve(){
    lli n;
    cin>>n;
    lli a[n+1],t[n+1];
    fr(i,1,n+1)cin>>a[i];
    fr(i,1,n+1)cin>>t[i];
    map<lli,ve> m;
    multiset<pll,greater<pll>> s;
    fr(i,1,n+1){
        m[a[i]].pb(t[i]);
    }
    auto nxt=m.begin();
    lli ans=0;
    while(nxt!=m.end()){
        auto cur=nxt++;
        for(auto e:cur->S){
            s.insert(mp(e,cur->F));
        }
        lli sz=s.size();
        if(nxt!=m.end())sz=min(sz,nxt->F-cur->F);
        fr(i,0,sz){
            auto temp=s.begin();
            ans+=(temp->F*((cur->F+i)-temp->S));
            s.erase(s.begin());
        }
    }
    cout<<ans;
}

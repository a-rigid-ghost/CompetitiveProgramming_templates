////1-based

struct dsu{
    lli n;
    ve par,val;
    
    dsu (lli x){
        n=x;
        par.assign(n+5,0);
        val.assign(n+5,0);
        fr(i,1,n+1){
            par[i]=i;
            val[i]=1;
        }
    }
    
    lli find(lli x){
        if(par[x]!=x){
            par[x]=find(par[x]);
        }
        return par[x];
    }
    
    void merge(lli x,lli y){
        lli xr=find(x),yr=find(y);
        if(xr==yr) return;
        if(val[xr]<val[yr])swap(xr,yr);
        par[yr]=xr;
        val[xr]+=val[yr];
    }
    
};

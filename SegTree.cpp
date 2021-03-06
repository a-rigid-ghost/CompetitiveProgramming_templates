///////////////////// General Segtree Point Update { add val to (id) and find query in (ql,qr) }

struct node{
    /// initialise with useless values so out of range elements won't affect the answer
    lli num=1e18;
};

struct segtree{
    lli n;
    ve a;
    vector<node> t;
    
    node merge(node a,node b){
        node res;
        if(a.num<b.num)res=a;
        else res=b;
        return res;
    }
    
    void build(lli i,lli l,lli r){
        if(l==r){
            t[i].num=a[l];
            return;
        }
        lli m=(l+r)/2;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
        t[i]=merge(t[2*i+1],t[2*i+2]);
    }
    
    segtree (ve arr){
        n=arr.size();
        t.assign(4*n+10,node());
        a=arr;
        build(0,0,n-1);
    }
    
    void update(lli i,lli l,lli r,lli val,lli id){
        if(l==r){
            t[i].num=val;
            return;
        }
        lli m=(l+r)/2;
        if(l<=id && id<=m)update(2*i+1,l,m,val,id);
        else update(2*i+2,m+1,r,val,id);
        t[i]=merge(t[2*i+1],t[2*i+2]);
    }
    
    node query(lli i,lli l,lli r,lli ql,lli qr){
        if(qr<l || r<ql)return node();
        if(ql<=l && r<=qr) return t[i];
        lli m=(l+r)/2;
        return merge(query(2*i+1,l,m,ql,qr),query(2*i+2,m+1,r,ql,qr));
    }
};

////////////////////Maximum Subsegment

struct node{
    lli val,pre,suf,sum;
    node (){
        val=pre=suf=sum=-INF;
    }
    node (lli a){
        val=pre=suf=sum=a;
    }
};

struct Segtree{
    lli n;
    ve a;
    vector<node> t;
    
    node merge(node a,node b){
        node res;
        res.val=max({a.val,b.val,a.suf+b.pre});
        res.pre=max(a.pre,a.sum+b.pre);
        res.suf=max(a.suf+b.sum,b.suf);
        if(min(a.sum,b.sum)==-INF)res.sum=-INF;
        else res.sum=a.sum+b.sum;
        return res;
    }
    
    void build(lli i,lli l,lli r){
        if(l==r){
            t[i]=node(a[l]);
            return;
        }
        lli m=(l+r)/2;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
        t[i]=merge(t[2*i+1],t[2*i+2]);
    }
    
    Segtree(ve arr){
        n=arr.size();
        t.resize(4*n+10);
        a=arr;
        build(0,0,n-1);
    }
    
    node query(lli i,lli l,lli r,lli ql,lli qr){
        if(qr<l || r<ql)return node();
        if(ql<=l && r<=qr) return t[i];
        lli m=(l+r)/2;
        return merge(query(2*i+1,l,m,ql,qr),query(2*i+2,m+1,r,ql,qr));
    }
};

///////////////////// LAZY prop point query { add val to (ql,qr) and find value at a give index }

struct lazypoint{
    lli n;
    ve lazy,a;
    
    void build(lli i,lli l,lli r){
        if(l==r){
            lazy[i]=a[l];
            return;
        }
        lli m=(l+r)/2;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
    }
    
    void init(ve arr){
        n=arr.size();
        lazy.assign(4*n+10,0);
        a=arr;
        build(0,0,n-1);
    }
    
    void push(lli i,lli l,lli r){
        if(l==r)return;
        lazy[2*i+1]+=lazy[i];
        lazy[2*i+2]+=lazy[i];
        lazy[i]=0;
    }
    
    void update(lli i,lli l,lli r,lli val,lli ql,lli qr){
        push(i,l,r);
        if(qr<l || r<ql)return;
        if(ql<=l && r<=qr){
            lazy[i]+=val;
            return;
        }
        lli m=(l+r)/2;
        update(2*i+1,l,m,val,ql,qr);
        update(2*i+2,m+1,r,val,ql,qr);
    }
    
    lli query(lli i,lli l,lli r,lli id){
        push(i,l,r);
        if(l==r)return lazy[i];
        lli m=(l+r)/2;
        if(l<=id && id<=m)return query(2*i+1,l,m,id);
        return query(2*i+2,m+1,r,id);
    }
};

///////////////////// LAZY prop range query { add val to (ql,qr) and find minimum in a given range }

struct lazyrange{
    lli n;
    ve t,lazy,a;
    
    void build(lli i,lli l,lli r){
        if(l==r){
            t[i]=a[l];
            return;
        }
        lli m=(l+r)/2;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
        t[i]=min(t[2*i+1],t[2*i+2]);
    }
    
    void init(ve arr){
        n=arr.size();
        t.assign(4*n+10,0);
        lazy.assign(4*n+10,0);
        a=arr;
        build(0,0,n-1);
    }
    
    void push(lli i,lli l,lli r){
        t[i]+=lazy[i];
        if(l!=r){
            lazy[2*i+1]+=lazy[i];
            lazy[2*i+2]+=lazy[i];
        }
        lazy[i]=0;
    }
    
    void update(lli i,lli l,lli r,lli val,lli ql,lli qr){
        push(i,l,r);
        if(qr<l || r<ql)return;
        if(ql<=l && r<=qr){
            lazy[i]+=val;
            push(i,l,r);
            return;
        }
        lli m=(l+r)/2;
        update(2*i+1,l,m,val,ql,qr);
        update(2*i+2,m+1,r,val,ql,qr);
        t[i]=min(t[2*i+1],t[2*i+2]);
    }
    
    lli query(lli i,lli l,lli r,lli ql,lli qr){
        if(qr<l || r<ql)return 1e18;
        push(i,l,r);
        if(ql<=l && r<=qr) return t[i];
        lli m=(l+r)/2;
        return min(query(2*i+1,l,m,ql,qr),query(2*i+2,m+1,r,ql,qr));
    }
};

///////////////////// LAZY prop range query { add val to (ql,qr) and find sum in a given range }

struct lazyrange{
    lli n;
    ve t,lazy,a;
    
    void build(lli i,lli l,lli r){
        if(l==r){
            t[i]=a[l];
            return;
        }
        lli m=(l+r)/2;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
        t[i]=t[2*i+1]+t[2*i+2];
    }
    
    lazyrange (ve arr){
        n=arr.size();
        t.assign(4*n+10,0);
        lazy.assign(4*n+10,0);
        a=arr;
        build(0,0,n-1);
    }
    
    void push(lli i,lli l,lli r){
        t[i]+=(r-l+1)*lazy[i];
        if(l!=r){
            lazy[2*i+1]+=lazy[i];
            lazy[2*i+2]+=lazy[i];
        }
        lazy[i]=0;
    }
    
    void update(lli i,lli l,lli r,lli val,lli ql,lli qr){
        push(i,l,r);
        if(qr<l || r<ql)return;
        if(ql<=l && r<=qr){
            lazy[i]+=val;
            push(i,l,r);
            return;
        }
        lli m=(l+r)/2;
        update(2*i+1,l,m,val,ql,qr);
        update(2*i+2,m+1,r,val,ql,qr);
        t[i]=t[2*i+1]+t[2*i+2];
    }
    
    lli query(lli i,lli l,lli r,lli ql,lli qr){
        if(qr<l || r<ql)return 0;
        push(i,l,r);
        if(ql<=l && r<=qr) return t[i];
        lli m=(l+r)/2;
        return query(2*i+1,l,m,ql,qr)+query(2*i+2,m+1,r,ql,qr);
    }
};

//////// range max update, range max query, query number stored in node for backtracking

struct node{
    lli val=0,id=0;
};

node merge(node a,node b){
    if(a.val>b.val) return a;
    return b;
}

struct lazyrange{
    lli n;
    vector<node> t,lazy,a;
    
    void build(lli i,lli l,lli r){
        if(l==r){
            t[i]=a[l];
            return;
        }
        lli m=(l+r)>>1;
        build(2*i+1,l,m);
        build(2*i+2,m+1,r);
        t[i]=merge(t[2*i+1],t[2*i+2]);
    }
    
    lazyrange (vector<node> arr){
        n=arr.size();
        t.resize(4*n+10,{0,0});
        lazy.resize(4*n+10,{0,0});
        a=arr;
    }
    
    void push(lli i,lli l,lli r){
        if(lazy[i].val==0) return;
        t[i]=merge(t[i],lazy[i]);
        if(l!=r){
            lazy[2*i+1]=merge(lazy[i],lazy[2*i+1]);
            lazy[2*i+2]=merge(lazy[i],lazy[2*i+2]);
        }
        lazy[i].val=0;
        lazy[i].id=0;
    }
    
    void update(lli i,lli l,lli r,node val,lli ql,lli qr){
        push(i,l,r);
        if(qr<l || r<ql)return;
        if(ql<=l && r<=qr){
            lazy[i]=merge(lazy[i],val);
            push(i,l,r);
            return;
        }
        lli m=(l+r)>>1;
        update(2*i+1,l,m,val,ql,qr);
        update(2*i+2,m+1,r,val,ql,qr);
        t[i]=merge(t[2*i+1],t[2*i+2]);
    }
    
    node query(lli i,lli l,lli r,lli ql,lli qr){
        if(qr<l || r<ql)return {0,0};
        push(i,l,r);
        if(ql<=l && r<=qr) return t[i];
        lli m=(l+r)>>1;
        return merge(query(2*i+1,l,m,ql,qr),query(2*i+2,m+1,r,ql,qr));
    }
};

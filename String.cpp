//KMP-prefix_func

ve prefunc(string s){
    lli n=s.size();
    ve pref(n,0);
    fr(i,1,n){
        lli j=pref[i-1];
        while(s[j]!=s[i] && j>0){
            j=pref[j-1];
        }
        if(s[i]==s[j])pref[i]=j+1;
    }
    return pref;
}

//Z-func

ve zfunc(string s) {
    lli n=s.length();
    ve z(n,0);
    lli l=0,r=0;
    fr(i,1,n){
        if(i<=r)z[i] = min (r - i + 1, z[i - l]);
        while(i+z[i]<n && s[z[i]]==s[i + z[i]]) z[i]++;
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
    return z;
}

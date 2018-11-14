class dsu{
public:
    int maxno;
    vi ranke,sz,root;
    dsu(int k){
        maxno=k;
        ranke.resize(k+1);
        sz.resize(k+1,1);
        root.resize(k+1);
        iota(root.begin(),root.end(),0);
    }
    int findroot(int x){return (x==root[x])?x:(root[x]=findroot(root[x]));}
    void unite(int &x,int &y){
        int a=findroot(x),b=findroot(y);
        if(a==b)    return ;
        if(ranke[a]>ranke[b]){
            root[b]=a;
            sz[a]+=sz[b];
            return ;
        }
        root[a]=b;
        sz[b]+=sz[a];
        ranke[b]+=(ranke[a]==ranke[b]);
    }
};

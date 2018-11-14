int tim=0,l;
vector <vi> adj,up;
vi tin,tout;
void init(int sz){
    for(;(1<<l)<=sz;l++);
    adj.resize(sz+1); tin.resize(sz+1); tout.resize(sz+1); up.resize(sz+1);
    loop(i,0,sz+1)
        up[i].resize(l+1,0);
}
void dfs(int src,int par){
    tin[src]=++tim;
    up[src][0]=par;
    loop(i,1,l+1)
        up[src][i]=up[up[src][i-1] ][i-1];
    for(auto i:adj[src])
        if(i!=par)
            dfs(i,src);
    tout[src]=++tim;
}
bool is_ancestor(int u,int v){
    if(u==0 or v==0)  return false ;
    return (tin[u]<tin[v] and tout[u]>tout[v]);
}
int lca(int u,int v){
    if(is_ancestor(u,v))    return u;
    if(is_ancestor(v,u))    return v;
    for(int i=l;i>=0;i--)
        if(!is_ancestor(up[u][i],v) and up[u][i]!=0)
            u=up[u][i];
    return up[u][0];
}

#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100],top;
vector<bool> vis(100);
int n,ed,x,y;
void dfs(int src){
    for(auto &ele:adj[src]){
        if(!vis[ele]){
            vis[ele]=1;
            dfs(ele);
        }
    }
    top.emplace_back(src);
}
int main(){
    //cout<< "Enter number of vertex and number of edges\n";
    cin>>n>>ed;
    //cout<< "Enter those edges\n";
    for(int i=0;i<ed;i++){
        cin>>x>>y;
        adj[x].emplace_back(y);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
            vis[i]=1,
            dfs(i);
    reverse(top.begin(),top.end());
    for(auto &ele:top)
        cout<<ele<< ' '; 
}

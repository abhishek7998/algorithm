#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pii pair<int,int> 

vector<vector<pii> > g,g1;
vector<vector<int> > ans;

vector<int> dijkstra(int n,int s){
        priority_queue<pii,vector<pii>,greater<pii> > q;
        vector<int> d(n+1,1e8);
        d[s]=0;
        q.push(mp(d[s],s));
        while(!q.empty()){
                pii z=q.top();
                q.pop();
                int p=z.second;
                for(int j=0;j<g[p].size();j++){
                        if( d[p] + g[p][j].second < d[g[p][j].first] ){
                                d[g[p][j].first] = d[p] + g[p][j].second;
                                q.push(mp(d[g[p][j].first] , g[p][j].first));
                        }
                }
        }
        d.erase(d.begin());
        return d;
}

vector<int> bellmanford(int n){
        vector<int> d(n+1,1e9);
        int i,j,k;
        d[0]=0;
        for(k=0;k<n;k++){
                for(i=0;i<=n;i++){
                        for(j=0;j<g1[i].size();j++){
                                if( d[i]+ g1[i][j].second < d[g1[i][j].first] ) 
                                        d[g1[i][j].first]= d[i]+ g1[i][j].second;
                        }
                }
        }
        return d;
}

int main(){
        int n,e,j,i,u,v,d;
        cin>>n>>e;
        g.assign(n+1,vector<pii>());
        
        for(i=0;i<e;i++){
                cin>>u>>v>>d;
                g[u].push_back(make_pair(v,d));
        }
        g1=g;
        for(i=1;i<=n;i++)
                g1[0].push_back(make_pair(i,0));
        
        vector<int> h=bellmanford(n);
        
        for(i=0;i<=n;i++){
                for(j=0;j<g[i].size();j++){
                        g[i][j].second+=h[i]-h[g[i][j].first];                        
                }       
        }
        
        for(i=1;i<=n;i++){
                ans.push_back(dijkstra(n,i));
        }
        
        for(i=0;i<ans.size();i++){
                for(j=0;j<ans[i].size();j++)
                        ans[i][j]-=h[i+1]-h[j+1];
        }              
        
                
        cout<<"Distance matrix\n";
        for(i=0;i<ans.size();i++){
                for(j=0;j<ans[i].size();j++)
                        cout<<ans[i][j]<<" ";
                cout<<endl;
        }              
}

/*
        
5 9
1 3 2
3 2 4
1 3 8
4 1 2
1 5 -4
5 4 6
4 3 -5
2 5 7
2 4 1
*/

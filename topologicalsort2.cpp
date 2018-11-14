#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,x,y;
    cin>>n>>m;                             //seee one more topological file
    vector<int>v[n+1];
    bool vis[n]={0};
    int indeg[n]={0};
    vector<int>print;
    queue<int>q;
    for(int i=0;i<m;i++)
    {
       cin>>x>>y;
       v[x].push_back(y);
       indeg[y]++;
    }
    for(int i=0;i<n;i++)
    {
        if(indeg[i]==0)
        {
        vis[i]=1;
        q.push(i);
        }
    }
    while(!q.empty())
    {
       int p=q.front();
        print.push_back(p);//cout<<p<<" ";
        q.pop();
        for(int i=0;i<v[p].size();i++)
        {
           if(vis[v[p][i]]==0)
           {  indeg[v[p][i]]--;
		      if(indeg[v[p][i]]==0)
		       {
			    vis[v[p][i]]=1;
               q.push(v[p][i]);
               }
            }
		}
    }
    //sort(print.begin(),print.end());
    for(int i=0;i<print.size();i++)
    {
        cout<<print[i]<<" ";
    }
}

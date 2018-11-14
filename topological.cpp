#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector <int,int> v[20];
    int n,m;
    cin>>n>>m;
    int indegree[n+1];
    memset(indegree,0,sizeof indegree);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        indegree[y]++;
    }
    multiset <int> ms;
    for(int i=1;i<=n;i++)
    {
        if(indegree[i]==0)
        ms.insert(i);
    }
    vector <int> v;
    queue <int> q;
    int str=*ms.begin();
    multiset<int>::iterator itr;
    for(itr=ms.begin();itr!=ms.end();itr++)
    {
        int i=*itr;
        q.push(itr);
        v.push_back(i);
    }
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
stack <int> s;
vector <int> adj[50];
vector <int> adjtrans[50];
int c=0;
bool vis[50];
void dfstime(int sr)
{
	vis[sr]=true;
	for(int i=0;i<adj[sr].size();i++)
	{
		if(vis[adj[sr][i]]==false)
		{
			dfstime(adj[sr][i]);
		}
	}
	s.push(sr);
}
void dfs(int sr)
{
	//cout<<sr<<" ";
	vis[sr]=true;
	c++;
	for(int i=0;i<adjtrans[sr].size();i++)
	{
		if(vis[adjtrans[sr][i]]==false)
		{
			dfs(adjtrans[sr][i]);

		}
	}
}
int main()
{
	memset(vis,false,sizeof vis);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin>>x>>y;
		adj[x].push_back(y);
		adjtrans[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==false)
		{
			dfstime(i);
		}
	}
	memset(vis,false,sizeof(vis));
	int odd=0;
	int even=0;
	//cout<<s.size()<<" ";
	/*while(!s.empty())
	{
		cout<<s.top()<<"\n";
		s.pop();
	}*/
	while(!s.empty())
	{
		int v=s.top();
		s.pop();
		//cout<<v<<"\n";
		if(vis[v]==false)
		{
			c=0;
			dfs(v);
			//cout<<"\n";
			if(c%2==1)
			{
				odd+=c;
			}
			else
			{
				even+=c;
			}
		}
	}
	//cout<<odd<<" "<<even<<" ";
	cout<<odd-even;
	return 0;
}

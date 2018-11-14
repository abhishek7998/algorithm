#include<bits/stdc++.h>
using namespace std;
# define Pr pair<int,int>
class node
{
	public:
	node *parent,*left,*right,*child;
	pair<int,int> data;
	int degree;
	bool mark;
	node(int d,int m)
	{
		data.first=d;
		data.second=m;
		degree=0;
		parent=left=right=child=NULL;
		mark=false;
	}
	node* concatenate(node *h)
	{
		node *x=left;
		node *y=h->left;
		x->right=h;
		h->left=x;
		y->right=this;
		left=y;
		if(h->data.first<data.first)
			return h;
		return this;
	}
};
class fib_heap
{
	public:
	node *head;
	fib_heap()
	{
		head=NULL;
	}
	bool isEmpty()
	{
		return head==NULL;
	}
	void concatenate(node *h)
	{
		if(head==NULL)
		{
			head=h;
			return;
		}
		if(h==NULL)
			return ;
		head=head->concatenate(h);
	}
	void insert(int val,int m)
	{
		node *x=new node(val,m);
		x->left=x;
		x->right=x;
		concatenate(x);		
	}
	pair<int,int> extractMin()
	{
		node *z=head;
		node *c=z->child;
		do
		{
			if(!c)
				break;
			c->parent=NULL;
			c=c->right;
		}while(c!=z->child);
		z->child=NULL;
		concatenate(c);
		if(head->left==head)
		{
			head=NULL;
			return z->data;
		}	
		z->left->right=z->right;
		z->right->left=z->left;
		head=z->left;
		consolidate();
		return z->data;
	}
	void consolidate()
	{
		int maxDegree=0;
		node *x=head;
		int cnt=1;
		do
		{
			cnt++;
			maxDegree=max(maxDegree,x->degree);
			x=x->right;
		}while(x!=head);
		//cerr<<"done"<<endl;
		maxDegree+=cnt;
		node* A[maxDegree];
		for(int i=0;i<maxDegree;i++)
			A[i]=0;
		int maxYet=0;
		head->left->right=NULL;
		while(head)
		{
			node *next=head->right;
			head->left=head;
			head->right=head;
			int d=head->degree;
			while(A[d]!=NULL)
			{
				node *y=A[d];
				if(head->data.first>y->data.first)
				{
					node *z=head;
					head=y;
					y=z;
				}
				A[d]=NULL;	
				head=link(head,y);
				d++;
			}
			A[d]=head;
			maxYet=max(maxYet,d);
			head=next;	
		}
		head=NULL;
		for(int i=0;i<=maxYet;i++)
			concatenate(A[i]);		
	}	
	node* link(node *a,node *b)
	{
		a->degree++;
		b->parent=a;
		if(a->child==NULL)
			a->child=b;
		else
			a->child=(a->child)->concatenate(b);
		return a;
	}
	node* find(node* nd,int v)
	{
		if(nd==NULL)
			return nd;
		if(nd->data.first==v)
			return nd;
		node *f=find(nd->child,v);
		if(f!=NULL)
			return f;
		node *cp=nd->right;
		while(cp!=nd)
		{
			f=find(cp,v);
			if(f!=NULL)
				return f;
			cp=cp->right;
		}
		return NULL;
	}
	bool decreaseKey(int ov,int nv)
	{
		if(nv>=ov)
			return false;
		node *f=find(head,ov);
		if(f==NULL)
			return false;
		f->data.first=nv;
		if(f->parent!=NULL&&f->parent->data.first>f->data.first)
		{
			node *par=f->parent;
			cut(f);
			cascadingCut(par);
		}
		if(f->data.first<head->data.first)
			head=f;
		return true;
	}	
	void cut(node *x)
	{
		node *p=x->parent;
		p->child=remove(p->child,x);
		p->degree--;
		x->left=x;
		x->right=x;
		x->parent=NULL;
		x->mark=false;
		concatenate(x);
	}
	void cascadingCut(node *x)
	{
		node *p=x->parent;
		if(p!=NULL)
		{
			if(x->mark==false)
				x->mark=true;
			else
			{
				cut(x);
				cascadingCut(p);	
			}
 
		}
	}
 
	void findis(node* nd)
	{
		if(nd==NULL)
			return ;
		cout<<nd->data.first<<" ";
		findis(nd->child);
 
	}
 
 
 
	void display()
	{
			node* ptr=head;
			if(ptr==NULL)
				{cout<<"empty heap"<<endl;
				return;}
			cout<<"displaying heap :\n";
			do
			{
				findis(ptr);
				ptr=ptr->right;
			}while(ptr!=head);
			cout<<endl;
	}
 
	node* remove(node *l,node *x)
	{
 
		if(l->left==l)
			return NULL;
		x->left->right=x->right;
		x->right->left=x->left;
		node *cp1=l,*cp2=l;
		do
		{
			if(cp2->data.first<cp1->data.first)
				cp1=cp2;
			cp2=cp2->right;
		}while(cp2!=l);
		return cp1;
	}
	pair<int,int> getMin()
	{
		return head->data;
	}
	bool deleteKey(int v)
	{
		if(!decreaseKey(v,INT_MIN))
			return false;
		extractMin();
		return true;
	}
};
 
 
void printpath(int path[],int i)
{
	cout<<i<<" ";
	while(path[i]!=i)
	{
	i=path[i];
	cout<<i<<" ";
	}	
 
}
 
 
void dijkstra(int src,vector<pair<int,int> > graph[],int n )
{
int  dist[n];
int path[n];
for(int i=0;i<n;i++)
	{dist[i]=1e8; path[i]=i;}
dist[src]=0;
fib_heap h;
h.insert(0,src);
while(h.isEmpty()!=true)
{
pair<int,int> p=h.extractMin();
int u=p.first;
for(int i=0;i<graph[u].size();i++)
{
	int v=graph[u][i].first;
	if(dist[v]>dist[u]+graph[u][i].second)
	{
		dist[v]=dist[u]+graph[u][i].second;
		path[v]=u;
		h.insert(v,dist[v]);
	}
 
}
 
}
 
for(int i=0;i<n;i++)
{
if(dist[i]<12346)
	{printpath(path,i);
	cout<<"cost is "<<dist[i]<<endl;}
else if(i==src)
	cout<<i<<" is source itself so dist= 0 "<<endl;
else
	cout<<"path is not there"<<endl;
 
 
}
 
 
}
 
 
int main()
{
	fib_heap h;
	int n,e;
	cout<<"enter the no of nodes and edges  "<<endl;
	cin>>n>>e;
		vector< pair<int,int> > graph[n];
		for(int i=0;i<e;i++)
		{
		int s,d,w;
		cin>>s>>d>>w;
		graph[s].push_back(make_pair(d,w));
		graph[d].push_back(make_pair(s,w));
		}
		int so;
		cout<<"enter the source "<<endl;
		cin>>so;
		dijkstra(so,graph,n);
}	

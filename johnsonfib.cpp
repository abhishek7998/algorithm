#include<bits/stdc++.h>
using namespace std;
struct Node
{
	pair<int,int> val;
	int degree;
	Node *left,*right,*parent,*child;
	bool mark;
	Node(pair<int,int> x)
	{
		val=x;degree=0;mark=0;left=right=parent=child=0;
	}
};
class Heap{
    public:
    int n;
    Node *minRoot;map<pair<int,int>,Node*> m;
    Heap(Node* x){
	//n =0;
        x->right=x;x->left=x;
        minRoot=x;n=1;
    }
    Heap(){
        n=0;minRoot=0;
    }
    bool empty()
    {
	    return minRoot!=NULL?false:true;
    }
    void Union(Heap h2)
    {
	    n=n+h2.n;
            Node *min1=this->minRoot,*min2=h2.minRoot;
	    if(!min1){
		minRoot=min2;return;
	    }
	    if(!min2){
		return;
	    }
	    Node *x=min1->left,*y=min2->left; //x - left child in min[H1] and y - left child in min[H2]
	    x->right=min2; min2->left=x;
	    y->right=min1; min1->left=y;
	    (min1->val).first<(min2->val).first?minRoot=min1:minRoot=min2; //making root to minimum element in new heap
    }
    void insert(pair<int,int> a)
    {
		Node* x=new Node(a); // creating node variable
        	m[a]=x;
		x->left=x;x->right=x;
        	Heap h2(x);	// creating new heap from new node
		Union(h2);      // Union of two heap
    }
    Node* extract_min()
    {
        if(!minRoot){
		cout<<"Heap is EMPTY\n";
		return 0;
	}
	Node* z=minRoot; // stores the min element to return
	Node* it=z->child;//exploring all child and concatenate
	while(it!=0)
        {
            Node* next=DeleteRoot(it);//n--;// deletes child node
            Heap h2(it); // create separate heap tree from deleted child node
	    Union(h2); // concatenate the two heaps
            it->parent=0;
            it=next;
	}
        minRoot=DeleteRoot(z); // deletes minimum element from root list and assign minRoot = z->right
	    consolidate();n--;
        m.erase(m.find(z->val));//keep every element distinct
        return z;
    }
    void consolidate()
    {
	    Node* a[100];
	    for(int i=0;i<100;i++)
	    a[i]=0;
        Node* it=minRoot;
        while(it!=0)
        {
            Node* x=it;int d=x->degree;
            it=minRoot=DeleteRoot(x);
            while(a[d]!=0)
            {
                Node* y=a[d];
                if((x->val).first>(y->val).first)
			swap(x,y);
                Link(x,y);a[d]=0;d+=1;
            }
            a[d]=x;
        }
        this->minRoot=NULL;
        for(int i=0;i<100;i++)
        {
            if(a[i])
            {
                Heap h2(a[i]);Union(h2);
            }
        }
    }
    void Link(Node* x,Node* y)
    {
        Node* temp=x->child;x->child=y;y->parent=x;
        if(temp){
            y->right=temp;y->left=temp->left;
            temp->left->right=y;
            temp->left=y;
        }
        else {
	    y->right=y;y->left=y;
	    }
        x->degree++;
        y->mark=false;
    }
    Node* DeleteRoot(Node* x)
    {
        if(x->right==x)return 0;
        else
        {
            x->left->right=x->right;x->right->left=x->left;
            return x->right;
        }
    }
    void decrease_key(Node* x,int k)
    {
	    if(x==NULL)
	    {
		    cout << "No such value exist to decrease" << endl;
		    return;
	    }
        if(k>(x->val).first)
        {
            cout<<"ERROR\n";
            return;
        }
	    pair<int,int> x_val = x->val; // to modified map
        (x->val).first=k;
    	int t1 = x_val.second;
	    m.erase(m.find(x_val)); // modifying map
	    m[make_pair(k,t1)] = x; // modifying map
        Node* y=x->parent;
        if(y&&(x->val).first<(y->val).first)
        {
            cut(x,y);
            cascading_cut(y);
        }
        if((x->val).first<(minRoot->val).first)
        	minRoot=x;
    }
    void cut(Node* x,Node* y)
    {
        Node* temp=DeleteRoot(x);
        y->child=temp;
        //n--;//work_around
        Heap h2(x);Union(h2);
        x->parent=0;x->mark=false;
    }
    void cascading_cut(Node* y)
    {
        Node* z=y->parent;
        if(z)
        {
            if(!y->mark) // if y is unmarked then mark y
            {
                y->mark=true;
            }
            else
            {
                cut(y,z);
                cascading_cut(z);
            }
        }
    }
    void Delete(Node* x)
    {
        if(!x)
        {
            cout<<"No such element\n";
            return;
        }
        decrease_key(x,INT_MIN);
        Node* z=extract_min();
    }
};
vector<int> dijkshtra(vector<pair<int,int> > adj[],int s,int n)
{
	vector<bool> vis(n+1,false);
	Heap heap;
	heap.insert(make_pair(0,s));
	vector<int> dist(n);
	for(int i=0;i<=n;i++)
	{
		dist[i] = INT_MAX;
	}
	dist[s] = 0;
	while(!heap.empty())
	{
		Node* m = heap.extract_min();
		pair<int,int> p = m->val;
		int src = p.second;
		int wt = p.first;
		if(vis[src])
			continue;
		vis[src] = true;
		for(int i=0;i<adj[src].size();i++)
		{
			pair<int,int> nxt = adj[src][i];
			if(dist[src]!=INT_MAX && dist[src]+nxt.first<dist[nxt.second])
			{
				dist[nxt.second] = dist[src]+nxt.first;
				heap.insert(make_pair(dist[nxt.second],nxt.second));
			}
		}
	}
	return dist;
}
 
vector<int> bellmanFord(int s,vector<int> edges[],int n,int e)
{
    vector<int> dist(n+1);
 
    for(int i=0;i<=n;i++)
    {
        dist[i]=INT_MAX;
    }
 
    dist[s] = 0;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<e;j++)
        {
            int u = edges[j][0];
            int v = edges[j][1];
            int w = edges[j][2];
            if(dist[u]!=INT_MAX && (dist[u]+w<dist[v]))
            {
                dist[v] = dist[u]+w;
            }
        }
    }
    return dist;
}
 
int main()
{
    int n,e;
    cout << "enter number of vertices and edges"<<endl;
    cin >> n >> e;
    cout << "enter source,destination and weight" << endl;
    int src,dest,wt;
    vector<int> edges[e+n];
    vector<pair<int,int> > adj[n+1];
    for(int i=0;i<e;i++)
    {
        cin >> src >> dest >> wt;
        edges[i].push_back(src);
        edges[i].push_back(dest);
        edges[i].push_back(wt);
    }
    for(int i=0;i<n;i++)
    {
        edges[i+e].push_back(n);
        edges[i+e].push_back(i);
        edges[i+e].push_back(0);
    }
    vector<int> h = bellmanFord(n,edges,n,e+n);
    for(int i=0;i<e;i++)
    {
        wt = edges[i][2];
        src = edges[i][0];
        dest = edges[i][1];
        wt = wt + h[src] - h[dest];
        adj[src].push_back(make_pair(wt,dest));
    }
    vector<vector<int> > shortestPathMatrix;
    for(int i=0;i<n;i++)
    {
        vector<int> temp=dijkshtra(adj,i,n);
        for(int j=0;j<n;j++)
        {
            if(temp[j]!=INT_MAX)
                temp[j] = temp[j]+h[j]-h[i];
        }
        shortestPathMatrix.push_back(temp);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(shortestPathMatrix[i][j]!=INT_MAX)
            {
                cout << shortestPathMatrix[i][j] << "  ";
            }
            else{
                cout << "INF ";
            }
        }
        cout << endl;
    }
    return 0;
}

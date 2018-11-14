#include<iostream>
using namespace std;

int k;

struct Node
{
	int point[20];
	Node *left,*right;
	Node(int p[])
	{
		for(int i=0;i<k;i++)
			point[i]=p[i];
		left=right=NULL;
	}
	Node()
	{
	}
};

Node *insert(Node *root,Node *point,int depth)
{
	if(root==NULL)
	{
		root = point;
		return root;
	}
	int cd = depth%k;
	
	if(point->point[cd] < root->point[cd])
		root->left = insert(root->left,point,depth+1);
	else
		root->right = insert(root->right,point,depth+1);
	return root;
}

bool same(Node *root,Node *point)
{
	for(int i=0;i<k;i++)
		if(root->point[i]!=point->point[i])
			return false;
	return true;
}

bool search(Node *root,Node *point,int depth)
{
	if(root==NULL)
		return false;
	if(same(root,point))
		return true;
	
	int cd = depth%2;

	if(root->point[cd] > point->point[cd])
		return search(root->left,point,depth+1);
	else
		return search(root->right,point,depth+1);
}

int main()
{
	int choice;
	cout<<"Enter k: ";
	cin>>k;
	Node *root=NULL,*point;
	int p[k],i;
	while(1)
	{
		cout<<"1.Insert Point\n2.Search Point\n3.Exit\n\nEnter Your Choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"Enter Point of "<<k<<" dimensions :";
				for(i=0;i<k;i++)
					cin>>p[i];
				point = new Node(p);
				if(!search(root,point,0))
				{
					root=insert(root,point,0);
					cout<<"Inserted Successfully.\n";
				}
				else
					cout<<"Point is already in the data.\n";
				break;
			case 2:
				cout<<"Enter Point of "<<k<<" dimensions :";
				for(i=0;i<k;i++)
					cin>>p[i];
				point = new Node(p);
				if(search(root,point,0))
					cout<<"Found.\n";
				else
					cout<<"Not Found.\n";
				break;
			case 3:
				cout<<"Exiting.\n";
				return 0;
		}
	}
}

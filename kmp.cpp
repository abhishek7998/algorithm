#include<bits/stdc++.h>
using namespace std;
int main()
{
	while(1)
	{
	string str;
	cout<<"type the string\n";
	cin>>str;
	int len=str.length();
	cout<<"type the pattern\n";
 string s;
 cin>>s;
int l=s.length();
int a[l];                        // time complexity to build this array a is o(n)
int j=0;                
int i=1;
a[0]=0;
for(int i=1;i<l;i++)         //lcp array is  made for pattern
{
	if(s[i]==s[j])
	{
		a[i]=j+1;
		j++;
	}
	else
	{
		if(j>0)
		{
			j=a[j-1];
			i--;
		}
		else
		a[i]=j;
	}
}
for(int i=0;i<l;i++)
cout<<a[i]<<" ";
cout<<"\n";
//cout<<"\nnow checking occur\n";
j=0;
for(int i=0;i<len;i++)             // time complexity to match this pattern a is o(n)
{
	if(j==l)
	{                                          //total=(n+m)  n=legth of string given   m=length=patterm
		break;
	}
	else
	{
		if(str[i]==s[j])
		{
			j++;
		}
		else
		{
			if(j==0)
			{
				continue;
			}	
			else 
			{
			 if(i!=0 && j>0)
			{
			 j=a[j-1];
			 i--;
		    }
		}
	}
}
}
	if(j==l)
	{
		cout<<"yes\n";
	}
		else
		{
			cout<<"no\n";
		}
	//	cout<<j<<"\n";
	cout<<"\n";
}
}

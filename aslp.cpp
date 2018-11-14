#include<iostream>
using namespace std;

int minimum(int x,int y)
{
    if(x<=y)
        return x;
    else
        return y;
}

int main()
{
    int n,i,j,e1,x1,e2,x2,fastest;
    int a[10][10],t[10][10],f[10][10];
    cout<<"Enter the no. of activity of each station:-\n";
    cin>>n;
    cout<<"Enter the activities-\n";
    for(i=1;i<=2;i++)
        for(j=1;j<=n;j++)
            cin>>a[i][j];
    cout<<"Enter the entry and exit of line 1\n";
    cin>>e1>>x1;
    cout<<"Enter the entry and exit of line 2\n";
    cin>>e2>>x2;
    cout<<"Enter the travelling cost from line 1 to line 2(t1j) or line 2 to line 1(t2j)\n";
    for(i=1;i<=2;i++)
        for(j=1;j<n;j++)
            cin>>t[i][j];
    //f[i][j] is the fastest time to reach the station j from j-1 in line i
    f[1][1]=e1+a[1][1];
    f[2][1]=e2+a[2][1];
    if(f[1][1]<=f[2][1])
    {
        cout<<"1-->";
    }
    else
    {
        cout<<"2-->";
    }
    for(j=2;j<=n;j++)
    {
        f[1][j]=minimum((f[1][j-1]+a[1][j]),(f[2][j-1]+t[2][j-1]+a[1][j]));
        f[2][j]=minimum((f[2][j-1]+a[2][j]),(f[1][j-1]+t[1][j-1]+a[2][j]));
        if(f[1][j]<=f[2][j])
            cout<<"1-->";
        else
            cout<<"2-->";
    }
    fastest=minimum(f[1][n]+x1,f[2][n]+x2);
    if(f[1][n]+x1<f[2][n]+x2)
    {
    	cout<<"exit\n";
        cout<<"Line 1 denotes the line from which we are out\n";
    }
    else if(f[1][n]+x1>f[2][n]+x2)
    {
    	cout<<"exit\n";
        cout<<"Line 2 denotes the line from which we are out\n";
    }
    else
        cout<<"We can get out using any line for fastest time\n";
    cout<<"Minimum time required is:- "<<fastest<<endl;
    cout<<"\n";
    return 0;
}


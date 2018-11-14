#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"type the sample\n";
    string s;
    cin>>s;
    cout<<"type the pattern\n";
    string p;
    cin>>p;
    int pl;
    pl=p.length();
    int sl=s.length();
    cout<<pl<<" "<<sl<<"\n";
        int base=27;
    int fhash=0,temph=0;
    cout<<p[0]*3<<" "<<p[1]*97<<"\n";
    cout<<"\n";

    for(int i=0;i<pl;i++)
    {
        fhash+=p[i]*pow(base,i);
        cout<<fhash<<"\n";
        temph+=s[i]*pow(base,i);
        cout<<temph<<"\n";
    }
    if(temph==fhash)
    {
        cout<<"pattern found\n";
    }
    else
    {
    for(int i=1;i<sl-pl+1;i++)
    {
       temph=(temph-s[i-1])/base +s[i+pl-1]*pow(base,pl-1);
       cout<<fhash<<"\n";
       if(fhash==temph)
       {
           cout<<"from index "<<i<<" to "<<i+pl-1<<" yes\n";
           break;
       }
    }
    }
}

#include <bits/stdc++.h>
using namespace std;
int x,y,gcd,num1,num2;
void extendedeuclid(int a,int b){
    if(b==0){
        gcd=a;
        x=1,y=0;
        return ;
    }
    extendedeuclid(b,a%b);
    int temp=x;
    x=y;
    y=temp-(a/b)*y;
}
int main(){
    extendedeuclid(16,10);
    cout<<gcd<< ' '<<y<< ' ';
}

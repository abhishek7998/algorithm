#include <bits/stdc++.h>
using namespace std;
bool previous[100][100];
int vertex,edge,x,y;
int main(){
    //cout<< "Enter the number of vertices and number of edges\n";
    cin>>vertex>>edge;
    //cout<< "Enter those edges\n";
    for(int i=0;i<edge;i++){
        cin>>x>>y;
        previous[x][y]=1;
    }
    for(int i=1;i<=vertex;i++)
        previous[i][i]=1;
    int cnt=0;
    while(cnt<vertex-2){
        for(int from=1;from<=vertex;from++){
            for(int to=1;to<=vertex;to++){
                for(int go=1;go<=vertex;go++){
                    previous[from][to]|=(previous[from][go] and previous[go][to]);
                }
            }
        }
        cnt++;
    }
    for(int from=1;from<=vertex;from++){
        for(int to=1;to<=vertex;to++){
            cout<<previous[from][to]<<" \n"[to==vertex];
        };
    };
}

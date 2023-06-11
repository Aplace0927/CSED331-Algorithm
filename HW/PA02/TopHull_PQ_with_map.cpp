#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <utility>
#include <map>

using namespace std;

typedef struct{
    int X, Y;
    int sX, sY;
    bool Start;
}Point;

bool CmpPoint(Point& A, Point& B){
    if(A.X == B.X){
        return A.Y > B.Y;
    }
    return A.X < B.X;
}

map<pair<int, int>, int, greater<pair<int, int>>> M;
vector<Point> V;

int main(){
    int XS, XG, Y, N, TC;

    cin >> TC;
    for(int t = 0; t < TC; t++){
        cin >> N;

        V.clear();
        M.clear();
        for(int i = 0; i < N; i++){
            cin >> XS >> XG >> Y;
            V.push_back({XS, Y, XS, Y, true});
            V.push_back({XG, Y, XS, Y, false});
        }

        sort(V.begin(), V.end(), CmpPoint);
        
        int segHeight = V[0].Y;
        int segStart = V[0].X;
        bool noPrint;


        for(int v = 0; v < V.size(); v++){
            noPrint = M.empty();

            if(V[v].Start){
                M[{V[v].sY, V[v].sX}] = V[v].Y;
                if(segHeight != M.begin()->first.first){
                    if(!noPrint){
                        printf("%d %d %d\n", segStart, V[v].X, segHeight);
                    }
                    segStart = V[v].X;
                    segHeight = M.begin()->first.first;
                }
            }
            else{
                M.erase({V[v].sY,V[v].sX});
                if(!M.empty() && segHeight != M.begin()->first.first){
                    if(!noPrint){
                        printf("%d %d %d\n", segStart, V[v].X, segHeight);
                    }
                    segStart = V[v].X;
                    segHeight = M.begin()->first.first;
                }
                else if(M.empty()){
                    if(!noPrint){
                        printf("%d %d %d\n", segStart, V[v].X, segHeight);
                    }
                    segHeight = V[v].Y;
                    segStart = V[v].X;
                }
            }
        }
    }
    return 0;   
}
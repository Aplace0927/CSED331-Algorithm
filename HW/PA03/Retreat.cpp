#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef struct{
    int from;
    int to;
    int len;
    bool multi;
}Bridge;

vector<map<int, Bridge>> Adj;
vector<int> VisitOrder;


int N, M;
int idx;
long long Min = 21474836480;

int FindCut(int From, int To){
    int MyOrder = idx++, ChildOrder;
    VisitOrder[To] = MyOrder;

    for(auto v: Adj[To]){
        if(v.second.to != From){
            if(!VisitOrder[v.second.to]){
                ChildOrder = FindCut(To, v.second.to);
                MyOrder = min(MyOrder, ChildOrder);
                if(VisitOrder[To] < ChildOrder && Min > v.second.len && !v.second.multi){
                    Min = v.second.len;
                }
            }
            else{
                MyOrder = min(MyOrder, VisitOrder[v.second.to]);
            }
        }
    }
    VisitOrder[To] = MyOrder;
    return MyOrder;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int TC, From, To, Dist;
    cin >> TC;

    for(int t = 0; t < TC; t++){
        cin >> N >> M;

        Adj.clear();
        Adj.resize(N, map<int, Bridge>());

        for(int m = 0; m < M; m++){
            cin >> From >> To >> Dist;
            if(Adj[From].find(To) == Adj[From].end()){
                Adj[From][To] = {From, To, Dist, false};
                Adj[To][From] = {To, From, Dist, false};
            }
            else{
                Adj[From][To].multi = true;
                Adj[To][From].multi = true;
            }
        }

        idx = 1;
        Min = 21474836480;

        VisitOrder.clear();
        VisitOrder.resize(N, 0);
        
        FindCut(-1, 0);
        if(Min == 21474836480){
            Min = -1;
        }

        cout << Min << '\n';
    }
    return 0;
}
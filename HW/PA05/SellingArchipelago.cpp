#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

class Edge{
public:
    long long S, E, C;
    Edge(long long s, long long e, long long c): S(s), E(e), C(c) {};
};

vector<int> Parent;
vector<Edge> Bridge;

inline bool CostOrderAsc(Edge& A, Edge& B){return A.C < B.C;}
inline bool CostOrderDec(Edge& A, Edge& B){return A.C > B.C;}

int Find(int A){
    if(A == abs(Parent[A])){
        return Parent[A];
    }
    return Parent[A] = Find(abs(Parent[A]));
}

void Union(int A, int B){
    int fA = Find(A), fB = Find(B);
    Parent[abs(max(fA, fB))] = min(fA, fB);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int I, P, B, TC;
    set<int> Among;
    Among.clear();

    cin >> TC;
    while (TC--){
        cin >> I >> P >> B;

        Parent.clear();
        Bridge.clear();

        Parent.resize(I+1);
        for(int i = 1; i <= I; i++){Parent[i] = i;}

        long long Portal;
        for(int p = 0; p < P; p++){
            cin >> Portal;
            Parent[Portal+1] *= -1;
        }

        long long From, To, Cost;
        for(int b = 0; b < B; b++){
            cin >> From >> To >> Cost;
            Bridge.push_back(Edge(From+1, To+1, Cost));
        }

        long long ClusterCount = I - P + 1;
        sort(Bridge.begin(), Bridge.end(), CostOrderAsc);
        
        for(Edge &E: Bridge){
            if(!ClusterCount){
                break;
            }
            if(Find(E.S) < 0 && Find(E.E) < 0){
                continue;
            }
            if(Find(E.S) == Find(E.E)){
                continue;
            }
            Union(E.S, E.E);
            ClusterCount--;
        }
        
        sort(Bridge.begin(), Bridge.end(), CostOrderDec);

        Among.clear();

        long long BridgeAdd = P - 1;
        long long Costs = 0LL;

        for(Edge &E: Bridge){ 
            if(!BridgeAdd){
                break;
            }

            if(Parent[E.S] == Parent[E.E]){
                continue;
            }
            BridgeAdd--;
            long long renewS = Parent[E.S], renewE = Parent[E.E];
            for(int c = 1; c <= I; c++){
                if(Parent[c] == renewS || Parent[c] == renewE){
                    Parent[c] = max(renewS, renewE);
                }
            }
            Costs += E.C;
        }
        cout << Costs << '\n';
    }   
    return 0;   
}
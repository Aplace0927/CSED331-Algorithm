#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int P = 20230419;

vector<vector<int>> Adj;
vector<int> Arriving;
vector<int> CheckPoints;
vector<int> CP_TopOrd;
vector<int> WayCnt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M, TC;
    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        cin >> N >> M;

        Adj.clear();
        Arriving.clear();
        CheckPoints.clear();
        CP_TopOrd.clear();
        WayCnt.clear();

        Adj.resize(N);
        Arriving.resize(N, 0);
        CP_TopOrd.resize(N, 0);
        WayCnt.resize(N, 0);

        int From, To;
        for(int m = 0; m < M; m++){
            cin >> From >> To;
            Adj[From].push_back(To);
            Arriving[To]++;
        }

        int S, E, D, t;
        cin >> S >> E >> D;
        for(int d = 0; d < D; d++){
            cin >> t;
            CheckPoints.push_back(t);
        }

        sort(CheckPoints.begin(), CheckPoints.end());

        queue<int> Q;
        for(int i = 0; i < N; i++){
            if(!Arriving[i]){
                Q.push(i);
            }
        }

        WayCnt[S] = 1;
        int F;
        bool isCP;

        while(!Q.empty()){
            F = Q.front();
            Q.pop();

            isCP = binary_search(CheckPoints.begin(), CheckPoints.end(), F);
            CP_TopOrd[F] += int(isCP);

            for(int Next: Adj[F]){
                Arriving[Next]--;

                if(CP_TopOrd[F] == CP_TopOrd[Next]){
                    WayCnt[Next] += WayCnt[F];
                    WayCnt[Next] %= P;
                }
                else if(CP_TopOrd[F] > CP_TopOrd[Next]){
                    WayCnt[Next] = WayCnt[F];
                    CP_TopOrd[Next] = CP_TopOrd[F];
                }

                if(!Arriving[Next]){
                    Q.push(Next);
                }
            }
        }
        if(CP_TopOrd[E] != CheckPoints.size()){
            cout << 0 << '\n';
        }
        else{
            cout << WayCnt[E] % P << '\n';
        }
    }
    return 0;
}
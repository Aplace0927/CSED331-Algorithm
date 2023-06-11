 #include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <functional>

using namespace std;

using pLL = pair<long long, long long>;

const long long INF = 0x3FFFFFFFFFFFFFFF;

int N, M;
vector<vector<pLL>> AdjFwd;
vector<long long> DistFwd;
vector<vector<pLL>> AdjBwd;
vector<long long> DistBwd;

void Find(int S, vector<vector<pLL>>& Adj, vector<long long>& Dist){
    for(int i = 0; i < N; i++){
        Dist[i] = i == S ? 0 : INF;
    }
    priority_queue<pLL, vector<pLL>, greater<pLL>> PQ;

    PQ.push({0, S});
    pLL Top;

    while(!PQ.empty()){
        Top = PQ.top();
        PQ.pop();

        if(Dist[Top.second] < Top.first){
            continue;
        }

        for(pair<int, int> P: Adj[Top.second]){
            if(Dist[P.first] > Dist[Top.second] + P.second){
                Dist[P.first] = Dist[Top.second] + P.second;
                PQ.push({Dist[P.first], P.first});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        cin >> N >> M;
    
        AdjFwd.clear();
        DistFwd.clear();
        AdjBwd.clear();
        DistBwd.clear();

        AdjFwd.resize(N);
        DistFwd.resize(N);
        AdjBwd.resize(N);
        DistBwd.resize(N);

        long long From, To, Cost;
        bool multi;

        for(int m = 0; m < M; m++){
            cin >> From >> To >> Cost;
            multi = false;
            for(pLL &P: AdjFwd[From]){
                if(P.first == To){
                    P.second = min(P.second, Cost);
                    multi = true;
                }
            }
            if(!multi){
                AdjFwd[From].push_back({To, Cost});
            }
        }

        for(int n = 0; n < N; n++){
            for(pLL P: AdjFwd[n]){
                AdjBwd[P.first].push_back({n, P.second});
            }
        }

        Find(0, AdjFwd, DistFwd);
        Find(N-1, AdjBwd, DistBwd);


        long long MIN = INF;
        for(int i = 0; i < N; i++){
            for(pLL P: AdjFwd[i]){
                MIN = min(MIN, DistFwd[i] + DistBwd[P.first]);
            }
        }

        MIN = MIN == INF ? -1 : MIN;
        cout << MIN << endl;
    }
}
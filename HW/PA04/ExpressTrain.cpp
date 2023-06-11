#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

const long long INF = 0x3FFFFFFFFFFFFFFF;
using pLL = pair<long long, long long>;

class Subway{
public:
    long long To;
    long long Time;
    Subway(long long to, long long time): To(to), Time(time) {};
};

vector<vector<Subway>> Com;
vector<vector<Subway>> Exp;
vector<long long> Dist;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    long long N, M, ExpS, ExpE;
    int TC;
    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        cin >> N >> M >> ExpS >> ExpE;

        Com.clear();
        Exp.clear();
        Dist.clear();

        Com.resize(N);
        Exp.resize(N);
        Dist.resize(N, INF);
        Dist[0] = 0LL;

        long long From, To, Time, Xprs;

        for(int m = 0; m < M; m++){
            cin >> From >> To >> Time >> Xprs;
            if(Xprs == 0){
                Com[From].push_back(Subway(To, Time));
            }
            else if(Xprs == 1){
                Exp[From].push_back(Subway(To, Time));
            }     
        }

        priority_queue<pLL, vector<pLL>, greater<pLL>> PQ;

        PQ.push({0LL, 0});    // {AccumDist, Node}
        pLL T;

        while(!PQ.empty()){
            T = PQ.top();
            PQ.pop();
            
            if(Dist[T.second] < T.first){
                continue;
            }

            for(Subway &S: Com[T.second]){
                if(Dist[S.To] > Dist[T.second] + S.Time){    // IF new distance by commute train is shorter
                    Dist[S.To] = Dist[T.second] + S.Time;   // Update distance with commute train 
                    PQ.push({Dist[S.To], S.To});    // {Dist, Node}
                }
            }
            for(Subway &S: Exp[T.second]){
                if(Dist[S.To] > max(Dist[T.second], ExpS) + S.Time && max(Dist[T.second], ExpS) + S.Time <= ExpE){   // IF new distance by express train is shorter AND express train is available
                    Dist[S.To] = max(Dist[T.second], ExpS) + S.Time;    // Update distance with express train
                    PQ.push({Dist[S.To], S.To});    // {Dist, Node}
                }
            }
        }

        if(Dist[N-1] != INF){
            cout << Dist[N-1] << '\n';
        }
        else{
            cout << -1 << '\n';
        }
    }
    return 0;
}
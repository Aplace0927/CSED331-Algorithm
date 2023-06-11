#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
using pLL = pair<long long, long long>;

inline bool XComp(pLL A, pLL B){return A.first < B.first;}
inline bool YComp(pLL A, pLL B){return A.second < B.second;}

long long L1(pLL& L, pLL& R){
    return abs(L.first - R.first) + abs(L.second - R.second);
}


vector<pLL> V;
int N;

long long ClosestPairPoints(int L, int R){
    if(L + 1 == R){
        return L1(V[L], V[R]);
    }
    if(L + 2 == R){
        return min(L1(V[L], V[L+1]), min(L1(V[L+1], V[L+2]), L1(V[L], V[L+2])));
    }

    int M = (L + R) / 2;
    long long L_CPP = ClosestPairPoints(L, M);
    long long R_CPP = ClosestPairPoints(M+1, R); 
    long long Min_CPP = min(L_CPP, R_CPP);

    vector<pLL> Mid;
    for(int i = L; i <= R; i++){
        if(abs(V[i].first - V[M].first) < Min_CPP){
            Mid.push_back(V[i]);
        }
    }

    sort(Mid.begin(), Mid.end(), YComp);

    for(int i = 0; i < Mid.size(); i++){
        for(int j = max(0, i-12); j < min(int(Mid.size()), i+12); j++){
            if(i == j){
                continue;
            }
            Min_CPP = min(Min_CPP, L1(Mid[i], Mid[j]));
        }
    }

    return Min_CPP;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;

    for(int t = 0; t < TC; t++){
        V.clear();

        cin >> N;
        long long x, y;
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            V.push_back({x, y});
        }
        sort(V.begin(), V.end(), XComp);
        cout << ClosestPairPoints(0, N-1) << '\n';
    }
}
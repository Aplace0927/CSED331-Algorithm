#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

vector<vector<int>> toChild;
int memDP[5001][5001];

const int INF  = 0x3F3F3F3F;
int Cpy = 0;
int NonCpy = 0;

int FindMinStorageCnt(int Root, int DistFromRoot, int MaxDist){
    if(memDP[Root][DistFromRoot] != INF){
        Cpy++;
        return memDP[Root][DistFromRoot];
    }

    NonCpy++;
    int Temp = 0;
    for(int Child: toChild[Root]){
        if(DistFromRoot < MaxDist){
            Temp += min(FindMinStorageCnt(Child, DistFromRoot + 1, MaxDist), FindMinStorageCnt(Child, 0, MaxDist));
        }
        else{
            Temp += FindMinStorageCnt(Child, 0, MaxDist);
        }
    }

    if(DistFromRoot == 0){
        Temp += 1;
    }

    return memDP[Root][DistFromRoot] = min(Temp, memDP[Root][DistFromRoot]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, K, From, To, TC;
    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        cin >> N >> K;

        toChild.clear(); toChild.resize(N);

        for (int n = 0; n < N-1; n++){
            cin >> From >> To;
            toChild[From].push_back(To);
        }
        
        int S = 0, E = N, M = (S + E) / 2;
        while(S < E){
            M = (S + E) / 2;
            memset(memDP, 0x3F, sizeof(memDP));
            if(FindMinStorageCnt(0, 0, M) > K){
                S = M+1;
            }
            else{
                E = M;
            }
        }
        cout << S << '\n';
    }
    return 0;
}
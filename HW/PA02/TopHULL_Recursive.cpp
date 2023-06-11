#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct Building{
    long long  L, R, H;
    Building(long long l, long long r, long long h): L(l), R(r), H(h) {}
};

vector<Building> B;

vector<pair<int, int>> TopHull(int S, int E){
    if(S == E){
        return {{B[S].L, B[S].H}, {B[S].R, 0}};
    }
    
    int M = (S + E)/2;

    vector<pair<int, int>> Left = TopHull(S, M);
    vector<pair<int, int>> Right = TopHull(M+1, E);
    vector<pair<int, int>> Res;

    int i = 0, j = 0;
    int tL = 0, tR = 0;
    while(i < Left.size() && j < Right.size()){
        if(Left[i].first < Right[j].first){
            tL = Left[i].second;
            Res.push_back({Left[i++].first, max(tL, tR)});
        }
        else if(Left[i].first > Right[j].first){
            tR = Right[j].second;
            Res.push_back({Right[j++].first, max(tL, tR)});
        }
        else{
            tL = Left[i].second;
            tR = Right[j].second;
            Res.push_back({Left[i].first, max(tL, tR)});
            i++;
            j++;
        }
    }
    if(i == Left.size()){
        while(j < Right.size()){
            Res.push_back(Right[j++]);
        }
    }
    else{
        while(i < Left.size()){
            Res.push_back(Left[i++]);
        }
    }
    
    return Res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;
    for(int t = 0; t < TC; t++){
        int N;
        cin >> N;
        
        int L, R, H;

        B.clear();
        for(int i = 0; i < N; i++){
            cin >> L >> R >> H;
            B.push_back(Building(L, R, H));
        }
        
        vector<pair<int, int>> Top = TopHull(0, N-1);

        pair<int, int> Ptr = Top[0];
        for(int i = 0; i < Top.size(); i++){
            if(Top[i].second != Ptr.second){
                if(Ptr.second != 0){
                    cout << Ptr.first << " " << Top[i].first << " " << Ptr.second << '\n';
                }
                Ptr = Top[i];
            }
        }
    }
    return 0;
}
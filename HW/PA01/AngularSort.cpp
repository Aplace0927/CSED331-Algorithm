#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<pair<long long, long long>> V;

int Quad(pair<long long, long long> &P){
    if(P.first >= 0 && P.second > 0){return 1;}
    else if(P.first > 0 && P.second <= 0){return 2;}
    else if(P.first <= 0 && P.second < 0){return 3;}
    else if(P.first < 0 && P.second >= 0){return 4;}
}

bool CCW(int L, int R){
    int LQuad = Quad(V[L]), RQuad = Quad(V[R]);

    if(LQuad != RQuad){
        return LQuad < RQuad;
    }

    long long CrossPdct = V[L].first * V[R].second - V[R].first * V[L].second;

    if(CrossPdct != 0){
        return CrossPdct < 0;
    }

    return (V[L].first * V[L].first + V[L].second * V[L].second) < (V[R].first * V[R].first + V[R].second * V[R].second);
}

void AngMerge(int S, int M, int E){
    int Lptr = S;
    int Rptr = M+1;

    vector<pair<long long, long long>> T;

    while(Lptr <= M && Rptr <= E){
        if(CCW(Lptr, Rptr)){
            T.push_back(V[Lptr++]);
        }
        else{
            T.push_back(V[Rptr++]);
        }
    }
    if(Lptr == M+1){
        while(Rptr <= E){
            T.push_back(V[Rptr++]);
        }
    }
    else{
        while(Lptr <= M){
            T.push_back(V[Lptr++]);
        }
    }

    for(int i = 0; i < T.size(); i++){
        V[S+i] = T[i];
    }
}

void AngSort(int S, int E){
    if(S >= E){
        return;
    }

    //cout << S << "~" << E << endl;
    int M = (S+E) / 2;    
    AngSort(S, M);
    AngSort(M+1, E);
    AngMerge(S, M, E);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N, TC;
    long long x, y;
    
    cin >> TC;
    
    for(int t = 0; t < TC; t++){
        cin >> N;

        V.clear();

        for(int i = 0; i < N; i++){
            cin >> x >> y;
            V.push_back({x, y});
        }

        AngSort(0, N-1);

        for(pair<long long, long long> P : V){
            cout << P.first << " " << P.second << '\n';
        }
        cout << '\n';
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

vector<pair<long long, long long>> V;

bool Rotate(pair<long long, long long> A, pair<long long, long long> B){
    long long Ax = A.first - V[0].first, Ay = A.second - V[0].second;
    long long Bx = B.first - V[0].first, By = B.second - V[0].second;

    if(Ax*By - Bx*Ay == 0){
        return Ax*Ax + Ay*Ay < Bx*Bx + By*By;
    } 
    return Ax*By - Bx*Ay > 0;
}

pair<long long, long long> sub(pair<long long, long long> A, pair<long long, long long> B){
    return {A.first - B.first, A.second - B.second};
}

double Distance(pair<long long, long long> A, pair<long long, long long> B){
    return sqrt((B.first - A.first) * (B.first - A.first) + (B.second - A.second) * (B.second - A.second));
}

bool isCCW(pair<long long, long long> dA, pair<long long, long long> dB){
    return (dB.first * dA.second - dB.second * dA.first) < 0;
}

int main(){
    int TC;
    int N, x, y;
    
    cin >> TC;
    
    for(int i = 0; i < TC; i++){
        
        V.clear();

        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            V.push_back({x,y});
        }

        if(N == 2){
            printf("%.2lf\n", Distance(V[0], V[1]) * 2.0);
            continue;
        }

        sort(V.begin(), V.end());
        
        sort(V.begin() + 1, V.end(), Rotate);

        stack<pair<long long, long long>> S;
        
        S.push(V[0]);
        S.push(V[1]);

        pair<long long, long long> PS, PM;
        for(int i = 2; i < N; i++){
            while(S.size() >= 2){
                PM = S.top();
                S.pop();
                PS = S.top();
                if(isCCW(sub(PM, PS), sub(V[i], PM))){
                    S.push(PM);
                    break;
                }
            }
            S.push(V[i]);
        }

        pair<long long, long long> Mem;
        double Len = 0.0;

        Mem = S.top();
        Len += Distance(Mem, V[0]);
        
        S.pop();

        while(!S.empty()){
            Len += Distance(Mem, S.top());
            Mem = S.top();
            S.pop();
        }

        printf("%.2lf\n", Len);
    }
    return 0;
}
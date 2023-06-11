#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

bool Cmp(pair<long long, long long>& A, pair<long long, long long> &B){
    return A.first < B.first;
}

bool SlantCmp(pair<long long, long long> &A, pair<long long, long long> &B){
    return B.second * A.first - A.second * B.first > 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC, N;
    long long x, y;
    vector<pair<long long, long long>> V;

    cin >> TC;
    for(int t = 0; t < TC; t++){
        cin >> N;
        V.clear();
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            V.push_back({x, y});
        }
        sort(V.begin(), V.end(), Cmp);

        pair<long long, long long> MaxSlant = {abs(V[1].second - V[0].second), abs(V[1].first - V[0].first)};
        int MaxLoc = 0;
        for(int i = 0; i < V.size() - 1; i++){
            pair<long long, long long> Slant = {abs(V[i+1].second - V[i].second), abs(V[i+1].first - V[i].first)};
            if(SlantCmp(Slant, MaxSlant)){
                MaxSlant = Slant;
                MaxLoc = i;
            }
        }

        cout << V[MaxLoc].first << " " << V[MaxLoc].second << " " << V[MaxLoc+1].first << " " << V[MaxLoc+1].second << '\n';
    }
}
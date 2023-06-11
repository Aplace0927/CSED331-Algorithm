#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Hull{
public:
    long long S, E, H;
    Hull(long long s, long long e, long long h): S(s), E(e), H(h) {};
};
vector<Hull> V;

long long N, W;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;
    for(int tc = 0; tc < TC; tc++){
        cin >> N >> W;

        V.clear();
        V.resize(N+2, Hull(0,0,0));
        long long From, To, Height;
        for(int i = 1; i <= N; i++){
            cin >> From >> To >> Height;
            V[i] = Hull(From, To, Height);
        }
        V[N+1] = Hull(W, W, 0);

        stack<Hull> Mx;
        Mx.push({0LL, 0LL, 0LL});

        long long Area = 0LL;
        Hull T(0,0,0);

        for(int h = 1; h <= N+1; h++){
            while(!Mx.empty() && Mx.top().H > V[h].H){
                T = Mx.top();
                Mx.pop();
                Area = max(Area, T.H * (V[h-1].E - Mx.top().E));
            }

            Mx.push(V[h]);
        }
        cout << Area << '\n';
    }
    return 0;
}
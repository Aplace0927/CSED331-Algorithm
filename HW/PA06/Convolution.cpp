#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> V;
vector<vector<long long>> PrfSum;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC, R, C, N;
    cin >> TC;

    for(int tc = 0; tc < TC; tc++){
        cin >> R >> C >> N;
        V.clear();  PrfSum.clear();
        V.resize(R+1, vector<long long>(C+1));
        PrfSum.resize(R+1, vector<long long>(C+1, 0LL));
        
        for(int r = 1; r <= R; r++){
            for(int c = 1; c <= C; c++){
                cin >> V[r][c];
                PrfSum[r][c] = PrfSum[r][c-1] + PrfSum[r-1][c] - PrfSum[r-1][c-1] + V[r][c];
            }
        }
        for(int r = N; r <= R; r++){
            for(int c = N; c <= C; c++){
                cout << PrfSum[r][c] - PrfSum[r-N][c] - PrfSum[r][c-N] + PrfSum[r-N][c-N] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
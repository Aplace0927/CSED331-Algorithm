#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

struct Airport{
    long long x, y;
    long long sumX, sumY;
    long long manX, manY;
};
vector<Airport> V;

bool CmpX(Airport &A, Airport &B) {return A.x < B.x;}
bool CmpY(Airport &A, Airport &B) {return A.y < B.y;}
bool CmpMan(Airport &A, Airport &B) {return A.manX + A.manY < B.manX + B.manY;}

int main(){
    int TC, N;
    long long x, y;
    cin >> TC;

    for(int t = 0; t < TC; t++){
        V.clear();
        
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> x >> y;
            V.push_back({x, y, x, y, 0, 0});
        }
        sort(V.begin(), V.end(), CmpX);
        for(int i = 1; i < N; i++){
            V[i].sumX = V[i-1].sumX + V[i].x;
        }
        for(int piv = 0; piv < N; piv++){
            if(piv != 0){
                V[piv].manX += V[piv].x * piv - (V[piv-1].sumX);
            }
            if(piv != N-1){
                V[piv].manX += (V[N-1].sumX - V[piv].sumX) - V[piv].x * (N - piv - 1);
            }
        }

        sort(V.begin(), V.end(), CmpY);
        for(int i = 1; i < N; i++){
            V[i].sumY = V[i-1].sumY + V[i].y;
        }
        for(int piv = 0; piv < N; piv++){
            if(piv != 0){
                V[piv].manY += V[piv].y * piv - (V[piv-1].sumY);
            }
            if(piv != N-1){
                V[piv].manY += (V[N-1].sumY - V[piv].sumY) - V[piv].y * (N - piv - 1);
            }
        }

        sort(V.begin(), V.end(), CmpMan);

        cout << V[0].manX + V[0].manY << '\n';
    }

}
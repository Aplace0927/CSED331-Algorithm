#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<bool>> Visited;
vector<vector<long long>> Map;
vector<long long> Mem;

int N, M;
const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

bool Valid(int x, int y){
    return 0 <= x && x < N && 0 <= y && y < M;
}

bool BFS(int V){
    queue<pair<int, int>> Q;
    pair<int, int> Top;

    Q.push({0, 0});

    int newX, newY;

    while(!Q.empty()){
        Top = Q.front();
        Q.pop();

        if(Top.first == N-1 && Top.second == M-1){
            return true;
        }

        
        for(int i = 0; i < 4; i++){
            newX = Top.first + dx[i];
            newY = Top.second + dy[i];

            if(Valid(newX, newY) == true && Visited[newX][newY] == false && Map[newX][newY] >= V){
                Q.push({newX, newY});
                Visited[newX][newY] = true;
            }
        }
    }
    return false;
}


bool Drive(int Val){
    Visited.assign(N, vector<bool>(M, false));
    return BFS(Val);
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;
    for(int t = 0; t < TC; t++){
        cin >> N >> M;
        
        Visited.clear();
        Map.clear();
        Mem.clear();

        Visited.resize(N, vector<bool>(M, false));
        Map.resize(N, vector<long long>(M));

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                cin >> Map[i][j];
                Mem.push_back(Map[i][j]);
            }
        }

        sort(Mem.begin(), Mem.end());

        long long S = Mem.front(), E = Mem.back();
        long long Mid = (S + E) / 2;

        if(Drive(E)){
            cout << E << '\n';
            continue;
        }

        while(!(Drive(Mid) == true && Drive(Mid+1) == false)){
            cout << Mid << endl;
            Mid = (S + E) / 2;
            if(Drive(Mid) == true){
                S = Mid+1;
            }
            else{
                E = Mid;
            }
        }

        cout << Mid << '\n';
    }
}
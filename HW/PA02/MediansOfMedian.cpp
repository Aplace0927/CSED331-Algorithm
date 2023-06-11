#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> V;

int LinearSelection(vector<int> &V, int K){

    if(V.size() < 5 && V.size() > K){
        sort(V.begin(), V.end());
        return V[K];
    }

    vector<int> M;
    vector<int> Tmp;

    for(int i = 0; i < V.size(); i += 5){
        Tmp.clear();
        for(int j = 0; j < 5; j++){
            if(i + j >= V.size()){
                break;
            }
            Tmp.push_back(V[i+j]);
        }
        sort(Tmp.begin(), Tmp.end());
        M.push_back(Tmp[Tmp.size()/2]);
    }

    int Median = LinearSelection(M, M.size()/2);

    vector<int> Left, Right;
    int Medcnt = 0;

    for(int v: V){
        if(v < Median){
            Left.push_back(v);
        }
        else if(v == Median){
            Medcnt++;
        }
        else{
            Right.push_back(v);
        }
    }

    if(K < Left.size()){
        return LinearSelection(Left, K);
    }
    else if(Left.size() <= K && K < Left.size() + Medcnt){
        return Median;
    }
    else{
        return LinearSelection(Right, K - Left.size() - Medcnt);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int TC, N, c;

    cin >> TC;

    for(int t = 0; t < TC; t++){
        V.clear();

        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> c;
            V.push_back(c);
        }
        
        cout << LinearSelection(V, ((N+1)/2)-1) << endl;
    }
    return 0;
}
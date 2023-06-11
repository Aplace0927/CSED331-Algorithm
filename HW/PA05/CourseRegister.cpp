#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using pLL = pair<long long, long long>;
const long long MIN = -0x3FFFFFFFFFFFFFFF;

int N;
vector<pLL> Courses;

bool endCompare(pLL& A, pLL& B){
    return A.second < B.second;
}

int GreedyLearning(vector<pLL> &V){
    long long endTime = MIN;
    int CourseTakes = 0;
    for(pLL& P: V){
        if(P.first >= endTime){
            endTime = P.second;
            CourseTakes++;
        }
    }
    return CourseTakes;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int TC;
    cin >> TC;
    while(TC--){
        cin >> N;
        Courses.clear();

        int From, To;
        for(int n = 0; n < N; n++){
            cin >> From >> To;
            Courses.push_back({From, To});
        }
        sort(Courses.begin(), Courses.end(), endCompare);
        cout << GreedyLearning(Courses) << '\n';
    }
}

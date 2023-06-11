#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> DecimalSum(vector<int> A, vector<int> B){
    int SumSize = max(A.size(), B.size());

    A.resize(SumSize, 0);
    B.resize(SumSize, 0);
    
    vector<int> Res;

    int Carry = 0, SumDigit;
    for(int i = 0; i < A.size(); i++){
        SumDigit = A[i] + B[i] + Carry;
        Carry = SumDigit / 10;
        Res.push_back(SumDigit % 10);
    }
    if(Carry){
        Res.push_back(Carry);
    }
    return Res;
}

vector<int> DecimalSub(vector<int> A, vector<int> B){
    int SubSize = max(A.size(), B.size());

    A.resize(SubSize, 0);
    B.resize(SubSize, 0);
    
    vector<int> Res;

    int SubDigit;
    for(int i = 0; i < A.size(); i++){
        SubDigit = A[i] - B[i];
        if(SubDigit < 0){
            A[i+1]--;
            SubDigit += 10;
        }
        Res.push_back(SubDigit % 10);
    }
    return Res;
}

vector<int> DecimalMul(vector<int> A, vector<int> B){
    int MulSize = max(A.size(), B.size());

    if(MulSize <= 9){
        long long lA = 0, digA = 1;
        long long lB = 0, digB = 1;
        for(int i = 0; i < A.size(); i++){
            lA += A[i]*digA;
            digA *= 10;
        }
        for(int i = 0; i < B.size(); i++){
            lB += B[i]*digB;
            digB *= 10;
        }
        lA *= lB;
        vector<int> Res;
        while(lA){
            Res.push_back(lA%10);
            lA /= 10;
        }
        return Res;
    }

    A.resize(MulSize, 0);
    B.resize(MulSize, 0);

    vector<int> A_Lower(A.begin(), A.begin() + MulSize/2);
    vector<int> A_Upper(A.begin() + MulSize/2, A.end());
    vector<int> B_Lower(B.begin(), B.begin() + MulSize/2);
    vector<int> B_Upper(B.begin() + MulSize/2, B.end());
    
    vector<int> Lower = DecimalMul(A_Lower, B_Lower);
    vector<int> MulUpper = DecimalMul(A_Upper, B_Upper);
    vector<int> MulMiddl = DecimalMul(DecimalSum(A_Lower, A_Upper), DecimalSum(B_Lower, B_Upper));

    vector<int> Upper((MulSize/2)*2, 0);
    Upper.insert(Upper.end(), MulUpper.begin(), MulUpper.end());
    
    //cout << "--------" << endl;
    //cout << "Upper = "; for(auto u: Upper){cout << u;} cout << endl;
    //cout << "Lower = "; for(auto u: Lower){cout << u;} cout << endl;
    //cout << "MulMid = "; for(auto u: MulMiddl){cout << u;} cout << endl;

    MulMiddl = DecimalSub(MulMiddl, Lower);
    MulMiddl = DecimalSub(MulMiddl, MulUpper);

    vector<int> Middl(MulSize/2, 0);
    Middl.insert(Middl.end(), MulMiddl.begin(), MulMiddl.end());

    Upper = DecimalSum(Upper, Middl);
    Upper = DecimalSum(Upper, Lower);

    //for(auto a: A){cout << a;} cout << " * "; for(auto b: B){cout << b;} cout << " = "; for(auto u: Upper){cout << u;} cout << endl;
    return Upper;
}
int main(){
    string A, B;
    vector<int> iA, iB;
    int Minus = 0;

    cin >> A >> B;
    
    if(A == "0" || B == "0"){
        cout << 0;
        return 0;
    }

    if(A[0] == '-'){
        Minus++;
    }
    if(B[0] == '-'){
        Minus++;
    }

    for(auto a = A.rbegin(); a < A.rend(); a++){
        if(0 <= (*a - '0') && (*a - '0') <= 9){
            iA.push_back(*a - '0');
        }
    }

    for(auto b = B.rbegin(); b < B.rend(); b++){
        if(0 <= (*b - '0') && (*b - '0') <= 9){
            iB.push_back(*b - '0');
        }
    }

    vector<int> ResMul = DecimalMul(iA, iB);
    bool headZero = true;
    if(Minus%2 == 1){
        cout << "-";
    }
    for(auto vI = ResMul.rbegin(); vI < ResMul.rend(); vI++){
        if(headZero && *vI == 0){
            continue;
        }
        if(*vI != 0){
            headZero = false;
        }
        cout << *vI;
    }

    cout << endl;
    return 0;
}
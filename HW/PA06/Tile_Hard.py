Mat = [[3,1,-1],[1,0,0],[0,1,0]]
Org = [[1,0,0],[0,1,0],[0,0,1]]
Val = [[1,0,0],[0,1,0],[0,0,1]]

def MatMul(A, B):
    Res = []
    for i in range(len(A)):
        Temp = []
        for j in range(len(B[0])):
            Num = 0
            for k in range(len(B)):
                Num += A[i][k] * B[k][j]
            Temp.append(Num % 1_000_000_000)    # Hard version: 1_234_567_890
        Res.append(Temp)
    return Res

TC = int(input())
BaseCase = [1, 2, 7]

for _ in range(TC):
    N = int(input())
    Val = [[1,0,0],[0,1,0],[0,0,1]]

    if N <= 2:
        print(BaseCase[N])
    else:
        for B in str(bin(N - 2))[2:]:
            if(B == '1'):
                Val = MatMul(Val, Val)
                Val = MatMul(Val, Mat)
            else:
                Val = MatMul(Val, Val)
        print((Val[0][0]*BaseCase[2] + Val[0][1]*BaseCase[1] + Val[0][2]*BaseCase[0]) % 1_000_000_000)

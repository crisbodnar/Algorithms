#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory.h>

using namespace std;

ifstream fin("kfib.in");
ofstream fout("kfib.out");

const int MOD = 666013;

int K, M[2][2], REZ[2][2];

void Prod(int A[][2], int B[][2], int C[][2])
{
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                C[i][j] = (C[i][j] + 1LL * A[i][k] * B[k][j]) % MOD;
}

void Power(int X[][2], int p)
{
    int AUX[2][2];
    REZ[0][0] = REZ[1][1] = 1;

    for(; p; p >>= 1)
    {
        if(p & 1)
        {
            memset(AUX, 0, sizeof AUX);
            Prod(REZ, X, AUX);
            memcpy(REZ, AUX, sizeof AUX);
        }

        memset(AUX, 0, sizeof AUX);
        Prod(X, X, AUX);
        memcpy(X, AUX, sizeof AUX);
    }
}

int main()
{
    fin >> K;

    M[0][1] = M[1][0] = M[1][1] = 1;
    Power(M, K - 1);
    fout << REZ[1][1];
    return 0;
}

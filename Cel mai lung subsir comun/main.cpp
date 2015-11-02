#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("cmlsc.in");
ofstream fout("cmlsc.out");

const int NMAX = 1050;

int N, M, A[NMAX], B[NMAX], DP[NMAX][NMAX];
bool C[NMAX][NMAX];

void Build(int i, int j)
{
    if(!i || !j) return;

    if(C[i][j])
    {
        Build(i - 1, j - 1);
        fout << A[i] << ' ';
    }
    else
    {
        if(DP[i - 1][j] > DP[i][j - 1])
            Build(i - 1, j);
        else
            Build(i, j - 1);
    }
}

int main()
{
    fin >> N >> M;
    for(int i = 1; i <= N; i++)
        fin >> A[i];
    for(int i = 1; i <= M; i++)
        fin >> B[i];

    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++)
            if(A[i] == B[j])
                DP[i][j] = DP[i - 1][j - 1] + 1,
                C[i][j] = 1;
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);

    fout << DP[N][M] << '\n';
    Build(N, M);
    return 0;
}

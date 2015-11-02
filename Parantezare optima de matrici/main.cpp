#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("podm.in");
ofstream fout("podm.out");

const int NMAX = 550;
const long long oo = (1LL << 62);

long long N, D[NMAX], DP[NMAX][NMAX];

int main()
{
    fin >> N;
    for(int i = 0; i <= N; i++)
        fin >> D[i];

    for(int i = 1; i < N; i++) DP[i][i + 1] = D[i - 1] * D[i] * D[i + 1];
    for(int w = 2; w < N; w++)
        for(int i = 1; i <= N - w; i++)
        {
            int j = i + w;
            DP[i][j] = oo;
            for(int k = i; k < j; k++)
                DP[i][j] = min(DP[i][j], DP[i][k] + DP[k + 1][j] + D[i - 1] * D[k] * D[j]);
        }
    fout << DP[1][N];
    return 0;
}

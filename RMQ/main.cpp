#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

const int NMAX = 1e5 + 100;
const int LG = 17;

int N, M, V[NMAX], RMQ[LG][NMAX], lg[NMAX];

int main()
{
    fin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        fin >> V[i];
        RMQ[0][i] = V[i];
    }

    for(int i = 2; i <= N; i++)
        lg[i] = lg[(i >> 1)] + 1;

    for(int i = 1; (1 << i) <= N; i++)
        for(int j = 1; j <= N - (1 << i) + 1; j++)
        {
            int log = 1 << (i - 1);
            RMQ[i][j] = min(RMQ[i - 1][j], RMQ[i - 1][j + log]);
        }

    while(M--)
    {
        int x, y;
        fin >> x >> y;
        int log = lg[y - x + 1];
        fout << min(RMQ[log][x], RMQ[log][y - (1 << log) + 1]) << '\n';
    }
    return 0;
}

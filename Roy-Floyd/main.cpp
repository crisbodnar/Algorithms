#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

const int NMAX = 110;
const int oo = 0x3f3f3f3f;

int N, D[NMAX][NMAX];

int main()
{
    fin >> N;
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
        {
            fin >> D[i][j];
            if(i !=j && !D[i][j]) D[i][j] = oo;
        }

    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                if(i != j)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
            fout << D[i][j] << ' ';
        fout << '\n';
    }
    return 0;
}

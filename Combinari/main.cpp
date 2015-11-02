#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("combinari.in");
ofstream fout("combinari.out");

const int NMAX = 19;

int N, K, X[NMAX];

void Back(int k)
{
    if(k == K + 1)
    {
        for(int i = 1; i <= K; i++)
            fout << X[i] << ' ';
        fout << '\n';
    }
    else
        for(int j = X[k - 1] + 1; j <= N - K + k; j++)
        {
            X[k] = j;
            Back(k + 1);
        }
}

int main()
{
    fin >> N >> K;
    Back(1);
    return 0;
}

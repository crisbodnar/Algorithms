#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define i64 long long

using namespace std;

ifstream fin("ssnd.in");
ofstream fout("ssnd.out");

const int CMAX = 1e6 + 100;
const int MOD = 9973;

i64 T, N, ND, SD;
vector <bool> C(CMAX);
vector <int> D;

void Precomp()
{
    for(int i = 2; i <= 1e6; i++)
        if(!C[i])
        {
            D.push_back(i);
            for(int j = i + i; j <= 1e6; j += i)
                C[j] = 1;
        }
}

int POW(int x, int p)
{
    int rez = 1; x %= MOD;
    for(; p; p >>= 1)
    {
        if(p & 1)
            rez = (rez * x) % MOD;
        x = (x * x) % MOD;
    }
    return rez;
}

void Solve()
{
    ND = SD = 1;
    for(int i = 0; i < D.size() && 1LL * D[i] * D[i] <= N; i++)
        if(N % D[i] == 0)
        {
            int fr = 0;
            while(N % D[i] == 0)
                N /= D[i], fr++;
            ND *= (fr + 1);

            int pow1 = (POW(D[i], fr + 1) - 1) % MOD;
            int pow2 = (POW(D[i] - 1, MOD - 2)) % MOD;

            SD = (((SD * pow1) % MOD) * pow2) % MOD;
        }
    if(N > 1)
    {
        ND *= 2;
        SD = (1LL * SD * (N + 1)) % MOD;
    }

    fout << ND << ' ' << SD << '\n';
}

int main()
{
    Precomp();
    fin >> T;
    while(T--)
    {
        fin >> N;
        Solve();
    }
    return 0;
}

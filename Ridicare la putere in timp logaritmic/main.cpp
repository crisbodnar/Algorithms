#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("lgput.in");
ofstream fout("lgput.out");

const int MOD = 1999999973;

long long N, P;

long long POWER(long long n, long long p)
{
    long long rez = 1;
    for(; p; p >>= 1)
    {
        if(p & 1)
            rez = (rez * n) % MOD;
        n = (n * n) % MOD;
    }
    return rez;
}

int main()
{
    fin >> N >> P;
    fout << POWER(N, P);
    return 0;
}

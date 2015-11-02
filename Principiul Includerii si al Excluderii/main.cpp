#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("pinex.in");
ofstream fout("pinex.out");

const int MAX = 1e6 + 100;

long long M, A, B;
vector <bool> C(MAX);
vector <int> P, F;

void Precomp()
{
    for(int i = 2; i <= 1e6 + 10; i++)
        if(!C[i])
        {
            P.push_back(i);
            for(int j = i + i; j <= 1e6 + 10; j += i)
                C[j] = 1;
        }
}

void Solve()
{
    for(int i = 0; i < P.size() && P[i] * P[i] <= B; i++)
        if(B % P[i] == 0)
        {
            F.push_back(P[i]);
            while(B % P[i] == 0) B /= P[i];
        }
    if(B > 1)
        F.push_back(B);

    int N = F.size(); int confmax = (1 << N), n, sign;
    long long nr, sol = 0;
    for(int conf = 1; conf < confmax; conf++)
    {
        nr = 1; n = 0;
        for(int j = 0; j < N; j++)
            if(conf & (1 << j))
            {
                n++;
                nr *= 1LL * F[j];
            }
        if(n % 2) sign = 1;
        else sign = -1;
        sol += 1LL * sign * A / nr;
    }
    F.clear();
    fout << A - sol << '\n';
}

int main()
{
    Precomp();
    fin >> M;
    while(M--)
    {
        fin >> A >> B;
        Solve();
    }
    return 0;
}

//Kruskal

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

const int MMAX = 4e5 + 100;
const int NMAX = 2e5 + 100;

struct Muchie{
    int st, dr, d;
}MC[MMAX];

int N, M, T[NMAX], H[NMAX], sol;
vector <int> ARB;

bool cmp(const Muchie &A, const Muchie &B)
{
    return A.d < B.d;
}

int Find(int x)
{
    int tat, r = x, y = x;
    while(T[r]) r = T[r];

    while(y != r)
    {
        tat = T[y];
        T[y] = r;
        y = tat;
    }
    return r;
}

void Unite(int x, int y)
{
    if(H[x] > H[y]) T[y] = x;
    else
    {
        T[x] = y;
        if(H[x] == H[y]) H[y]++;
    }
}

int main()
{
    fin >> N >> M;
    fill(H + 1, H + N + 1, 1);

    for(int i = 1; i <= M; i++)
        fin >> MC[i].st >> MC[i].dr >> MC[i].d;
    sort(MC + 1, MC + M + 1, cmp);

    for(int i = 1; i <= M && ARB.size() < N; i++)
    {
        int st = MC[i].st, dr = MC[i].dr;
        st = Find(st), dr = Find(dr);
        if(st != dr)
        {
            Unite(st, dr);
            ARB.push_back(i);
            sol += MC[i].d;
        }
    }

    fout << sol << '\n' << ARB.size() << '\n';
    for(int i = 0; i < ARB.size(); i++)
        fout << MC[ARB[i]].st << ' ' << MC[ARB[i]].dr << '\n';
    return 0;
}

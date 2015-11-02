#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int NMAX = 1e5 + 100;

int N, nr, LG, AIB[NMAX], V[NMAX], A[NMAX], best[NMAX], t[NMAX];

bool Special()
{
    for(int i = 2; i <= N; i++)
        if(V[i] > V[i - 1]) return 0;
    return 1;
}

int CB(int val)
{
    int sol = 0;
    for(int lg = LG; lg; lg >>= 1)
        if(sol + lg <= nr && A[sol + lg] <= val)
            sol += lg;
    return sol;
}

void Update(int poz, int i)
{
    while(poz <= nr)
    {
        if(best[AIB[poz]] < best[i])
            AIB[poz] = i;
        poz += -poz&poz;
    }
}

int Query(int poz)
{
    int maxim = 0;
    while(poz)
    {
        if(best[maxim] < best[AIB[poz]])
            maxim = AIB[poz];
        poz -= -poz&poz;
    }
    return maxim;
}

void Afisare(int poz)
{
    if(t[poz]) Afisare(t[poz]);
    fout << V[poz] << ' ';
}

int main()
{
    fin >> N;

    for(int i = 1; i <= N; i++)
    {
        fin >> V[i];
        A[i] = V[i];
    }

    if(Special())
    {
        fout << 1 << '\n' << V[1];
        return 0;
    }

    sort(A + 1, A + N + 1); nr = 1;
    for(int i = 2; i <= N; i++)
        if(A[i] != A[nr]) A[++nr] = A[i];
    for(LG = 1; LG <= nr; LG <<= 1);

    int sol = 0;
    for(int i = 1; i <= N; i++)
    {
        int poz = CB(V[i]);
        t[i] = Query(poz - 1);
        best[i] = best[t[i]] + 1;
        Update(poz, i);
        if(best[sol] < best[i])
            sol = i;
    }

    fout << best[sol] << '\n';
    Afisare(sol);
    return 0;
}

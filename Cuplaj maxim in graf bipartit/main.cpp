#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define newn G[nod][i]

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

const int NMAX = 1e4 + 100;

int N, M, E, sol, st[NMAX], dr[NMAX];
bool viz[NMAX];
vector <int> G[NMAX];

bool Leaga(int nod)
{
    if(viz[nod]) return 0;
    viz[nod] = 1;
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(!dr[newn])
        {
            st[nod] = newn; dr[newn] = nod;
            return 1;
        }
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(Leaga(dr[newn]))
        {
            st[nod] = newn; dr[newn] = nod;
            return 1;
        }
    return 0;
}

int main()
{
    fin >> N >> M >> E;
    while(E--)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
    }

    bool ok = 1;
    while(ok)
    {
        ok = 0;
        fill(viz + 1, viz + N + 1, 0);
        for(int i = 1; i <= N; i++)
            if(!st[i] && Leaga(i)) ok = 1, sol++;
    }

    fout << sol << '\n';
    for(int i = 1; i <= N; i++)
        if(st[i]) fout << i << ' ' << st[i] << '\n';
    return 0;
}

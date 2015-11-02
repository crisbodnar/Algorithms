#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define newn G[nod][i]

using namespace std;

ifstream fin("lca.in");
ofstream fout("lca.out");

const int NMAX = 1e5 + 100;
const int EMAX = NMAX * 3;
const int LMAX = 18;

int N, M, nr, EUL[EMAX], H[EMAX], FIRST[NMAX], RMQ[LMAX][EMAX], LG[EMAX];
vector <int> G[NMAX];

void DFS(int nod, int lev)
{
    ++nr;
    EUL[nr] = nod;
    H[nr] = lev;
    FIRST[nod] = nr;
    for(unsigned i = 0; i < G[nod].size(); i++)
       {
           DFS(newn, lev + 1);
           EUL[++nr] = nod;
           H[nr] = lev;
       }
}

void Build_RMQ()
{
    for(int i = 2; i <= nr; i++)
        LG[i] = LG[(i >> 1)] + 1;
    for(int i = 1; i <= nr; i++)
        RMQ[0][i] = i;
    for(int i = 1; (1 << i) <= nr; i++)
        for(int j = 1; j <= nr - (1 << i); j++)
        {
            int lg2 = 1 << (i - 1);
            if(H[RMQ[i - 1][j]] < H[RMQ[i - 1][j + lg2]])
                RMQ[i][j] = RMQ[i - 1][j];
            else
                RMQ[i][j] = RMQ[i - 1][j + lg2];
        }
}

int LCA(int x, int y)
{
    x = FIRST[x], y = FIRST[y];
    if(x > y) swap(x, y);
    int lg2 = LG[y - x + 1], poz;
    if(H[RMQ[lg2][x]] < H[RMQ[lg2][y - (1 << lg2) + 1]])
        poz = RMQ[lg2][x];
    else
        poz = RMQ[lg2][y - (1 << lg2) + 1];
    return EUL[poz];
}

int main()
{
    fin >> N >> M;
    for(int i = 2; i <= N; i++)
    {
        int x; fin >> x;
        G[x].push_back(i);
    }

    DFS(1, 1);
    Build_RMQ();

    while(M--)
    {
        int x, y;
        fin >> x >> y;
        fout << LCA(x, y) << '\n';
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define newn G[nod][i]
#define fiu1 (nod << 1)
#define fiu2 (fiu1 + 1)
#define mid ((st + dr) >> 1)
#define nodl LANT[i][j]

using namespace std;

ifstream fin("heavypath.in");
ofstream fout("heavypath.out");

const int NMAX = 1e5 + 100;
const int oo = 0x3f3f3f3f;

int N, M, nrp = 1, V[NMAX], PLACE[NMAX], T[NMAX], DIM[NMAX], H[NMAX], P[NMAX], ARB[NMAX * 4];
vector <int> G[NMAX], LANT[NMAX];
vector <bool> viz(NMAX), uz(NMAX);

bool cmp (const int &a, const int &b) {return DIM[a] > DIM[b];}

void DFS(int nod, int height)
{
    viz[nod] = 1;
    DIM[nod]++;
    H[nod] = height;
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(!viz[newn])
        {
            DFS(newn, height + 1);
            DIM[nod] += DIM[newn];
        }
}

void Path(int nod, int path)
{
    viz[nod] = 0;
    PLACE[nod] = path;
    LANT[path].push_back(nod);
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(viz[newn])
        {
            if(!uz[nod])
            {
                uz[nod] = 1;
                Path(newn, path);
            }
            else
            {
                T[++nrp] = nod;
                Path(newn, nrp);
            }
        }
}

void Update(int nod, int st, int dr, int poz, int val, int fix)
{
    if(st == dr)
    {
        ARB[nod + fix] = val;
        return;
    }

    if(poz <= mid) Update(fiu1, st, mid, poz, val, fix);
    else Update(fiu2, mid + 1, dr, poz, val, fix);

    ARB[nod + fix] = max(ARB[fiu1 + fix], ARB[fiu2 + fix]);
}

int Query(int nod, int st, int dr, int left, int right, int fix)
{
    if(left > dr || st > right) return -oo;

    if(left <= st && dr <= right)
        return ARB[nod + fix];

    int rez = -oo;
    rez = max(rez, Query(fiu1, st, mid, left, right, fix));
    rez = max(rez, Query(fiu2, mid + 1, dr, left, right, fix));

    return rez;
}

int main()
{
    fin >> N >> M;
    for(int i = 1; i <= N; i++)
        fin >> V[i];
    for(int i = 1; i < N; i++)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, 1);
    for(int i = 1; i <= N; i++)
        sort(G[i].begin(), G[i].end(), cmp);
    Path(1, 1);

    for(int i = 1; i <= nrp; i++)
    {
        P[i] = P[i - 1] + LANT[i - 1].size() * 4;
        for(unsigned j = 0; j < LANT[i].size(); j++)
            Update(1, 1, LANT[i].size(), H[nodl] - H[T[i]], V[nodl], P[i]);
    }

    while(M--)
    {
        int tip, x, y;
        fin >> tip >> x >> y;
        if(!tip) Update(1, 1, LANT[PLACE[x]].size(), H[x] - H[T[PLACE[x]]], y, P[PLACE[x]]);
        else
        {
            int sol = -1;
            while(PLACE[x] != PLACE[y])
            {
                if(H[T[PLACE[x]]] < H[T[PLACE[y]]]) swap(x, y);
                sol = max(sol, Query(1, 1, LANT[PLACE[x]].size(), 1, H[x] - H[T[PLACE[x]]], P[PLACE[x]]));
                x = T[PLACE[x]];
            }
            if(H[x] < H[y]) swap(x, y);
            sol = max(sol, Query(1, 1, LANT[PLACE[x]].size(), H[y] - H[T[PLACE[x]]], H[x] - H[T[PLACE[x]]], P[PLACE[x]]));
            fout << sol << '\n';
        }
    }
    return 0;
}

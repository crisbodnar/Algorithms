//Prim
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define cc first
#define nn second
#define newn G[nod][i].nn
#define cost G[nod][i].cc

using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

const int NMAX = 2e5 + 100;
const int oo = 0x3f3f3f3f;

typedef pair <int, int> node;
vector <node> G[NMAX], ARB;
vector <bool> viz(NMAX);

int N, M, sol, V[NMAX], VEC[NMAX];
priority_queue <node, vector<node>, greater<node> > H;
priority_queue <node, vector<node>, greater<node> > P;

void Add(int nod)
{
    for(unsigned i = 0; i < G[nod].size(); i++)
    {
        V[newn] = min(V[newn], cost);
        if(V[newn] == cost) VEC[newn] = nod;
        if(!viz[newn]) H.push(node(V[newn], newn));
    }
}

int main()
{
    fin >> N >> M;
    fill(V + 1, V + N + 1, oo);

    while(M--)
    {
        int x, y, c;
        fin >> x >> y >> c;
        G[x].push_back(node(c, y));
        G[y].push_back(node(c, x));
    }

    V[1] = 0; viz[1] = 1;
    Add(1);

    for(int i = 1; i < N; i++)
    {
        while(viz[H.top().nn]) H.pop();
        int nod = H.top().nn;
        viz[nod] = 1;
        sol += V[nod];
        ARB.push_back(node(nod, VEC[nod]));
        Add(nod);
    }

    fout << sol << '\n' << ARB.size() << '\n';
    for(unsigned i =0; i < ARB.size(); i++)
        fout << ARB[i].first << ' ' << ARB[i].second << '\n';
    return 0;
}

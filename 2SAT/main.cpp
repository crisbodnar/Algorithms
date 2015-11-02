#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define newn G[nod][i]
#define Not(nr) ((nr) <= N ? (nr) + N : (nr) - N)

using namespace std;

ifstream fin("2sat.in");
ofstream fout("2sat.out");

const int NMAX = 2e5 + 100;

int N, M, V[NMAX];
vector <int> G[NMAX];
vector <bool> viz(NMAX);
queue <int> Q, Initialize;

void Clear()
{
    while(!Q.empty())
    {
        int nod = Q.front(); Q.pop();
        viz[nod] = viz[Not(nod)] = 0;
    }
}

bool DFS(int nod)
{
    Q.push(nod);
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(!viz[newn])
        {
            viz[newn] = viz[Not(newn)] = 1;
            V[newn] = 1; V[Not(newn)] = 0;
            if(!DFS(Not(newn)))
                return 0;
        }
        else if(!V[newn]) return 0;
    return 1;
}

bool Right(int nod, int tip)
{
    viz[nod] = viz[Not(nod)] = 1;
    V[nod] = tip; V[Not(nod)] = !tip;

    if(tip == 0)
        return DFS(nod);
    else
        return DFS(Not(nod));
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y;
        fin >> x >> y;
        if(x < 0) x = Not(-x);
        if(y < 0) y = Not(-y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for(int i = 1; i <= N; i++)
        if(!viz[i])
            if(!Right(i, 0))
            {
                Clear();
                if(!Right(i , 1))
                {
                    fout << "-1";
                    return 0;
                }
                Q = Initialize;
            }
    for(int i = 1; i <= N; i++)
        fout << V[i] << ' ';
    return 0;
}

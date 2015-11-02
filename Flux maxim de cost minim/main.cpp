#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>

#define newn G[nod][i]

using namespace std;

ifstream fin("fmcm.in");
ofstream fout("fmcm.out");

const int NMAX = 355;
const int oo = 0x3f3f3f3f;

int N, M, S, D, sol, DIST[NMAX], R[NMAX], OLD[NMAX],
T[NMAX], C[NMAX][NMAX], CST[NMAX][NMAX];
typedef pair <int, int> node;
vector <int> G[NMAX];
priority_queue <node, vector<node>, greater<node> > H;

bool BFS()
{
    memset(DIST, oo, sizeof DIST);
    DIST[S] = R[S] = 0;
    H.push(node(0, S));

    while(!H.empty())
    {
        int nod = H.top().second, val = H.top().first; H.pop();
        if(DIST[nod] != val) continue;

        for(unsigned i = 0; i < G[nod].size(); i++)
            if(C[nod][newn])
            {
                int cost = DIST[nod] + CST[nod][newn] + OLD[nod] - OLD[newn];
                if(DIST[newn] > cost)
                {
                    T[newn] = nod;
                    DIST[newn] = cost;
                    R[newn] = R[nod] + CST[nod][newn];
                    H.push(node(DIST[newn], newn));
                }
            }
    }
    memcpy(OLD, R, sizeof R);
    return (DIST[D] != oo);
}

void Update_Flux()
{
    int fmin = oo;
    for(int j = D; j != S; j = T[j])
        fmin = min(fmin, C[T[j]][j]);
    for(int j = D; j != S; j = T[j])
    {
        C[T[j]][j] -= fmin;
        C[j][T[j]] += fmin;
    }

    sol += R[D] * fmin;
}

int main()
{
    fin >> N >> M >> S >> D;
    while(M--)
    {
        int x, y, c, z;
        fin >> x >> y >> c >> z;
        G[x].push_back(y);
        G[y].push_back(x);
        C[x][y] = c;
        CST[x][y] = z;
        CST[y][x] = -z;
    }

    while(BFS())
        Update_Flux();
    fout << sol;
    return 0;
}

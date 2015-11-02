#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <queue>

#define newn G[nod][i]

using namespace std;

ifstream fin("cmcm.in");
ofstream fout("cmcm.out");

const int NMAX = 310 * 2;
const int oo = 0x3f3f3f3f;

int S, D, N, M, E, MC[NMAX][NMAX], F[NMAX][NMAX],
C[NMAX][NMAX], CST[NMAX][NMAX], DIST[NMAX], T[NMAX], OLD[NMAX], R[NMAX];
vector <int> G[NMAX];
typedef pair <int, int> node;
priority_queue <node, vector<node>, greater<node> > Q;

int sol, cmin;

void Add(int x, int y)
{
    G[x].push_back(y);
    G[y].push_back(x);
}

bool Dijkstra()
{
    memset(DIST, oo, sizeof DIST);
    DIST[S] = R[S] = 0; Q.push(node(0, S));
    while(!Q.empty())
    {
        int nod = Q.top().second, val = Q.top().first; Q.pop();
        if(DIST[nod] != val) continue;

        for(unsigned i = 0; i < G[nod].size(); i++)
            if(F[nod][newn] < C[nod][newn])
            {
                int cost = DIST[nod] + CST[nod][newn] + OLD[nod] - OLD[newn];
                if(cost < DIST[newn])
                {
                    T[newn] = nod;
                    DIST[newn] = cost;
                    R[newn] = R[nod] + CST[nod][newn];
                    Q.push(node(DIST[newn], newn));
                }
            }
    }
    memcpy(OLD, R, sizeof R);
    return DIST[D] != oo;
}

void Update_Flux()
{
    for(int j = D; j != S; j = T[j])
        F[T[j]][j]++, F[j][T[j]]--;
    sol++;
    cmin += R[D];
}

int main()
{
    fin >> N >> M >> E;
    D = N + M + 1;
    for(int i = 1; i <= E; i++)
    {
        int x, y, c;
        fin >> x >> y >> c; y += N;
        Add(S, x); Add(x, y); Add(y, D);
        C[S][x] = C[x][y] = C[y][D] = 1;
        CST[x][y] = c; CST[y][x] = -c;
        MC[x][y] = i;
    }

    while(Dijkstra())
        Update_Flux();
    fout << sol << ' ' << cmin << '\n';
    for(int i = 1; i <= N; i++)
        for(int j = N + 1; j <= N + M; j++)
            if(F[i][j] > 0)
                fout << MC[i][j] << ' ';
    return 0;
}

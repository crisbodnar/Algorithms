#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define newn G[nod][i]

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

const int NMAX = 1005;
const int oo = 0x3f3f3f3f;

int N, M, fmax, T[NMAX], F[NMAX][NMAX], C[NMAX][NMAX];
vector <int> G[NMAX];
vector <bool> viz(NMAX), inq(NMAX);
queue <int> Q;

bool BFS(int s)
{
    viz.assign(N + 1, 0); viz[s] = 1;
    inq.assign(N + 1, 0); inq[s] = 1;
    Q.push(s);

    while(!Q.empty())
    {
        int nod = Q.front(); Q.pop(); inq[nod] = 0;

        for(unsigned i =0; i < G[nod].size(); i++)
            if(F[nod][newn] < C[nod][newn])
                if(!viz[newn])
                {
                    viz[newn] = 1;
                    T[newn] = nod;
                    if(!inq[newn]) inq[newn] = 1, Q.push(newn);
                }
    }

    return viz[N];
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y, c;
        fin >> x >> y >> c;
        G[x].push_back(y);
        G[y].push_back(x);
        C[x][y] = c;
    }

    while(BFS(1))
    {
        for(int i = 1; i < N; i++)
            if(F[i][N] < C[i][N])
            {
                int fmin = C[i][N] - F[i][N];
                for(int j = i; j != 1; j = T[j])
                    fmin = min(fmin, C[T[j]][j] - F[T[j]][j]);
                for(int j = i; j != 1; j = T[j])
                {
                    F[T[j]][j] += fmin;
                    F[j][T[j]] -= fmin;
                }
                F[i][N] += fmin; F[N][i] -= fmin;
                fmax += fmin;
            }
    }
    fout << fmax;
    return 0;
}

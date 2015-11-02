#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define newn G[nod][i].second
#define newc G[nod][i].first

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

const int NMAX = 5e4 + 100;
const int oo = 0x3f3f3f3f;

int N, M, DIST[NMAX];
typedef pair <int, int> node;
vector <node> G[NMAX];
priority_queue <node, vector<node>, greater<node> > Q;

void Dijkstra()
{
    for(int i = 2; i <= N; i++)
        DIST[i] = oo;
    Q.push(node(0, 1));
    while(!Q.empty())
    {
        int nod = Q.top().second; Q.pop();

        for(unsigned i = 0; i < G[nod].size(); i++)
            if(DIST[newn] > DIST[nod] + newc)
            {
                DIST[newn] = DIST[nod] + newc;
                Q.push(node(DIST[newn], newn));
            }
    }
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y, c;
        fin >> x >> y >> c;
        G[x].push_back(node(c, y));
    }

    Dijkstra();
    for(int i = 2; i <= N; i++)
        if(DIST[i] != oo)
            fout << DIST[i] << ' ';
        else fout << "0 ";
    return 0;
}

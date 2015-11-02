#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define newn G[nod][i].second
#define newc G[nod][i].first

using namespace std;

ifstream fin("hamilton.in");
ofstream fout("hamilton.out");

const int NMAX = 18;
const int CMAX = (1 << NMAX);
const int oo = 0x3f3f3f3f;

int N, M, confmax, DP[CMAX][NMAX];
typedef pair <int, int> node;
vector <node> G[NMAX];

int Comp(int conf, int nod)
{
    if(DP[conf][nod] != -1) return DP[conf][nod];
    DP[conf][nod] = oo;

    for(unsigned i = 0; i < G[nod].size(); i++)
        if(conf & (1 << newn))
        {
            if(!newn && conf != (1 << nod) + 1) continue;
            DP[conf][nod] = min(DP[conf][nod], Comp(conf ^ (1 << nod), newn) + newc);
        }
    return DP[conf][nod];
}

int main()
{
    fin >> N >> M;
    confmax = (1 << N);
    while(M--)
    {
        int x, y, c;
        fin >> x >> y >> c;
        G[y].push_back(node(c, x)); // Retin muchia invers
    }

    int sol = oo;
    memset(DP, -1, sizeof DP); DP[1][0] = 0;
    for(unsigned i = 0; i < G[0].size(); i++)
        sol = min(sol, Comp(confmax - 1, G[0][i].second) + G[0][i].first);
    if(sol != oo) fout << sol;
    else fout << "Nu exista solutie";
    return 0;
}

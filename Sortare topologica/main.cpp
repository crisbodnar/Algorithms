#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int NMAX = 5e4 + 100;

int N, M;
vector <bool> viz(NMAX);
vector <int> G[NMAX], S;

void DFS(int nod)
{
    viz[nod] = 1;
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(!viz[G[nod][i]]) DFS(G[nod][i]);
    S.push_back(nod);
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
    }

    for(int i = 1; i <= N; i++)
        if(!viz[i])
            DFS(i);
    for(int i = S.size() - 1; i >= 0; i--)
        fout << S[i] << ' ';
    return 0;
}

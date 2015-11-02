#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define newn A[nod][i]
#define newn2 B[nod][i]

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int NMAX = 1e5 + 100;

int N, M, top, nrs, POST[NMAX];
vector <int> A[NMAX], B[NMAX], SOL[NMAX];
vector <bool> viz(NMAX);

void DFS(int nod)
{
    viz[nod] = 1;
    for(unsigned i = 0; i < A[nod].size(); i++)
        if(!viz[newn]) DFS(newn);
    POST[++top] = nod;
}

void DFST(int nod)
{
    viz[nod] = 0;
    SOL[nrs].push_back(nod);
    for(unsigned i = 0; i < B[nod].size(); i++)
        if(viz[newn2]) DFST(newn2);
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y;
        fin >> x >> y;
        A[x].push_back(y);
        B[y].push_back(x);
    }

    for(int i = 1; i <= N; i++)
        if(!viz[i]) DFS(i);

    for(int i = N; i ; i--)
        if(viz[POST[i]])
        {
            nrs++;
            DFST(POST[i]);
        }
    fout << nrs << '\n';
    for(int i = 1; i <= nrs; i++)
    {
        for(int j = 0; j < SOL[i].size(); j++)
            fout << SOL[i][j] << ' ';
        fout << '\n';
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>

#define newn G[nod][i]

using namespace std;

ifstream fin("biconex.in");
ofstream fout("biconex.out");

const int NMAX = 1e5 + 100;

int N, M, lev[NMAX], low[NMAX];
vector <int> G[NMAX];
vector <bool> viz(NMAX);
typedef pair<int, int> muchie;
vector < vector<int> > sol;
stack <muchie> st;

void Componenta_Biconexa(int x, int y)
{
    int tx, ty; vector <int> bx;
    do
    {
        tx = st.top().first, ty = st.top().second;
        bx.push_back(tx); bx.push_back(ty);
        st.pop();
    }while(tx != x || ty != y);
    sol.push_back(bx);
}

void DFS(int nod, int tat, int height)
{
    viz[nod] = 1; lev[nod] = low[nod] = height;
    for(unsigned i = 0; i < G[nod].size(); i++)
        if(!viz[newn])
        {
            st.push(muchie(nod, newn));
            DFS(newn, nod, height + 1);
            low[nod] = min(low[nod], low[newn]);
            if(low[newn] >= lev[nod]) Componenta_Biconexa(nod, newn);
        }
        else if(newn != tat) low[nod] = min(low[nod], lev[newn]);
}

int main()
{
    fin >> N >> M;
    while(M--)
    {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    DFS(1, 0, 1);
    fout << sol.size() << '\n';
    for(unsigned i = 0; i < sol.size(); i++)
    {
        sort(sol[i].begin(), sol[i].end());
        fout << sol[i][0] << ' ';
        for(unsigned j = 1; j < sol[i].size(); j++)
            if(sol[i][j] != sol[i][j - 1]) fout << sol[i][j] << ' ';
        fout << '\n';
    }
    return 0;
}

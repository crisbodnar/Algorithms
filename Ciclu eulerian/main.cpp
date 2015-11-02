#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

#define newn G[nod][i]

using namespace std;

ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

const int NMAX = 1e5 + 100;

int N, M;
vector <int> G[NMAX];
vector <bool> viz(NMAX);
queue <int> Q;
stack <int> st;

void BFS()
{
    Q.push(1); viz[1] = 1;
    while(!Q.empty())
    {
        int nod = Q.front(); Q.pop();
        for(unsigned i = 0; i< G[nod].size(); i++)
            if(!viz[newn])
            {
                viz[newn] = 1;
                Q.push(newn);
            }
    }
}

bool OK()
{
    for(int i = 1; i <= N; i++)
        if(G[i].size() & 1 || (!viz[i] && G[i].size()))
            return 0;
    return 1;
}

void Euler()
{
    st.push(1);
    while(!st.empty())
    {
        int nod = st.top();
        if(!G[nod].size())
        {
            st.pop();
            fout << nod << ' ';
        }
        else
        {
            int y = G[nod].back(); G[nod].pop_back();
            int i; for(i = 0; i < G[y].size() && G[y][i] != nod; i++);
            swap(G[y][i], G[y][G[y].size() - 1]); G[y].pop_back();
            st.push(y);
        }
    }
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

    BFS();

    if(OK()) Euler();
    else fout << "-1";
    return 0;
}

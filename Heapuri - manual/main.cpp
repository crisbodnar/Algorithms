#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#define tat (poz >> 1)
#define fiu1 (y << 1)
#define fiu2 (fiu1 + 1)

using namespace std;

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

const int NMAX = 2e5 + 100;

int top, lg, N, H[NMAX], P[NMAX], V[NMAX];

void Push(int poz)
{
    while(tat && V[H[poz]] < V[H[tat]])
    {
        swap(H[poz], H[tat]);
        P[H[poz]] = poz;
        P[H[tat]] = tat;

        poz = tat;
    }
}

void Pop(int poz)
{
    int y;
    while(poz != y)
    {
        y = poz;
        if(fiu1 <= lg && V[H[poz]] > V[H[fiu1]]) poz = fiu1;
        if(fiu2 <= lg && V[H[poz]] > V[H[fiu2]]) poz = fiu2;

        swap(H[poz], H[y]);
        P[H[poz]] = poz;
        P[H[y]] = y;
    }
}

int main()
{
    fin >> N;
    while(N--)
    {
        int tip, x;
        fin >> tip;
        if(tip == 1)
        {
            fin >> x;
            ++top; ++lg;
            P[top] = lg;
            V[top] = x;
            H[lg] = top;

            Push(lg);
        }
        else if(tip == 2)
        {
            fin >> x;
            V[x] = -1;
            Push(P[x]);

            P[H[1]] = 0;
            H[1] = H[lg--];
            P[H[1]] = 1;

            if(lg > 1) Pop(1);
        }
        else
            fout << V[H[1]] << '\n';
    }
    return 0;
}

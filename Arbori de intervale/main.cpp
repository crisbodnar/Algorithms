#include <iostream>
#include <fstream>

#define fiu1 (nod << 1)
#define fiu2 (fiu1 + 1)
#define mid ((st + dr) >> 1)

using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

const int NMAX = 1e5 + 100;

int N, M, poz, maxim, V[NMAX], ARB[NMAX * 3];

void BuildAI(int nod, int st, int dr)
{
    if(st == dr)
    {
        ARB[nod] = V[st];
        return;
    }

    BuildAI(fiu1, st, mid);
    BuildAI(fiu2, mid + 1, dr);
    ARB[nod] = max(ARB[fiu1], ARB[fiu2]);
}

void Update(int nod, int st, int dr, int val)
{
    if(st == dr)
    {
        ARB[nod] = val;
        return;
    }
    if(poz <= mid)
        Update(fiu1, st, mid, val);
    else
        Update(fiu2, mid + 1, dr, val);

    ARB[nod] = max(ARB[fiu1], ARB[fiu2]);
}

void Query(int nod, int st, int dr, int left, int right)
{
    if(right < st || dr < left) return;

    if(left <= st && dr <= right)
    {
        maxim = max(maxim, ARB[nod]);
        return;
    }

    Query(fiu1, st, mid, left, right);
    Query(fiu2, mid + 1, dr, left, right);
}

int main()
{
    fin >> N >> M;
    for(int i = 1; i <= N; i++)
        fin >> V[i];

    BuildAI(1, 1, N);
    while(M--)
    {
        int tip, a, b;
        fin >> tip >> a >> b;
        if(!tip)
        {
            maxim = -1;
            Query(1, 1, N, a, b);
            fout << maxim << '\n';
        }
        else
        {
            poz = a;
            Update(1, 1, N, b);
        }
    }
    return 0;
}

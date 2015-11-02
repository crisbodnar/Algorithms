#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

const int NMAX = 1e5 + 100;

int N, M, T[NMAX], H[NMAX];

int Find(int x)
{
    int r = x, y = x, tat;
    while(T[r]) r = T[r];

    while(y != r)
    {
        tat = T[y];
        T[y] = r;
        y = tat;
    }
    return r;
}

void Unite(int A, int B)
{
    if(H[A] > H[B]) T[B] = A;
    else
    {
        T[A] = B;
        if(H[A] == H[B]) H[B]++;
    }
}

int main()
{
    fin >> N >> M;
    fill(H + 1, H + N + 1, 1);

    while(M--)
    {
        int tip, a, b;
        fin >> tip >> a >> b;
        if(tip == 1)
            Unite(Find(a), Find(b));
        else
            if(Find(a) == Find(b))
                fout << "DA\n";
            else
                fout << "NU\n";
    }
    return 0;
}

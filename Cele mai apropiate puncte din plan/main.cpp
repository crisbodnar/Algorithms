#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#define i64 long long
#define mid ((st + dr) >> 1)

#define ff first
#define ss second

using namespace std;

ifstream fin("cmap.in");
ofstream fout("cmap.out");

const int NMAX = 1e5 + 100;
const long long oo = (1LL << 62);

int N;
typedef pair <i64, i64> pct;
vector <pct> X(NMAX), Y(NMAX), V(NMAX);

i64 Dist(pct A, pct B)
{
    return (B.ff - A.ff) * (B.ff - A.ff) + (B.ss - A.ss) * (B.ss - A.ss);
}

i64 DivImp(int st, int dr)
{
    if(st >= dr - 1) return oo;
    if(dr - st == 2)
    {
        if(Y[st] > Y[st + 1])
            swap(Y[st], Y[st + 1]);
        return Dist(X[st], X[st + 1]);
    }

    i64 best = min(DivImp(st, mid), DivImp(mid, dr));

    merge(Y.begin() + st, Y.begin() + mid, Y.begin() + mid, Y.begin() + dr, V.begin());
    copy(V.begin(), V.begin() + dr - st, Y.begin() + st);

    int vsize = 0;
    for(int i = st; i < dr; i++)
        if(abs(Y[i].ss - X[mid].ff) <= best)
            V[++vsize] = Y[i];
    for(int i = 1; i < vsize; i++)
        for(int j = i + 1; j <= vsize && j - i < 8; j++)
            best = min(best, Dist(V[i], V[j]));
    return best;
}

int main()
{
    fin >> N;
    for(int i = 0; i < N; i++)
        fin >> X[i].ff >> X[i].ss;
    sort(X.begin(), X.begin() + N);
    for(int i = 0; i < N; i++)
        Y[i].ff = X[i].ss, Y[i].ss = X[i].ff;
    fout.precision(6);
    fout << fixed << sqrt(DivImp(0, N));
    return 0;
}

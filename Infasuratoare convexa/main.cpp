#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#define xx first
#define yy second

using namespace std;

ifstream fin("infasuratoare.in");
ofstream fout("infasuratoare.out");

const int NMAX = 12e4 + 100;

int N, poz, top;
typedef pair <double, double> pct;
pct P[NMAX], st[NMAX];

double Sign(const pct &c, const pct &a, const pct &b)
{
    return (a.xx - c.xx) * (b.yy - c.yy) - (b.xx - c.xx) * (a.yy - c.yy);
}

bool cmp(const pct &a, const pct &b)
{
    return Sign(P[1], a, b) > 0;
}

int main()
{
    fin >> N; P[0].xx = P[0].yy = 1e9 + 100;
    for(int i = 1; i <= N; i++)
    {
        fin >> P[i].xx >> P[i].yy;
        if(P[poz].xx > P[i].xx) poz = i;
        else if(P[poz].xx == P[i].xx && P[poz].yy > P[i].yy) poz = i;
    }

    swap(P[1], P[poz]);
    sort(P + 2, P + N + 1, cmp);

    st[1] = P[1]; st[2] = P[2]; top = 2;
    for(int i = 3; i <= N; i++)
    {
        while(top > 1 && Sign(st[top - 1], st[top], P[i]) < 0)
            top--;
        st[++top] = P[i];
    }

    fout << top << '\n';
    fout.precision(6);
    for(int i = 1; i <= top; i++)
        fout << fixed << st[i].xx << ' ' << st[i].yy << '\n';
    return 0;
}

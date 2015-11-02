#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("aib.in");
ofstream fout("aib.out");

const int NMAX = 1e5 + 100;

int N, M, LG, AIB[NMAX];

void Add(int val, int poz)
{
    while(poz <= N)
    {
        AIB[poz] += val;
        poz += poz&-poz;
    }
}

int Sum(int poz)
{
    int s = 0;
    while(poz)
    {
        s += AIB[poz];
        poz -= -poz&poz;
    }
    return s;
}

int CB(int val)
{
    int sol = 0, aux = val;
    for(int lg = LG; lg; lg >>= 1)
        if(sol + lg <= N && AIB[sol + lg] < val)
            sol += lg, val -= AIB[sol]; sol++;
    if(Sum(sol) == aux) return sol;
    return -1;
}

int main()
{
    fin >> N >> M;
    for(LG = 1; LG <= N; LG <<= 1);
    for(int i = 1; i <=N; i++)
    {
        int x; fin >> x;
        Add(x, i);
    }

    while(M--)
    {
        int tip;
        fin >> tip;
        if(!tip)
        {
            int poz, val;
            fin >> poz >> val;
            Add(val, poz);
        }
        else if(tip == 1)
        {
            int a, b;
            fin >> a >> b;
            fout << Sum(b) - Sum(a - 1) << '\n';
        }
        else
        {
            int val;
            fin >> val;
            fout << CB(val) << '\n';
        }
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

ifstream fin("ahocorasick.in");
ofstream fout("ahocorasick.out");

const int AMAX = 1e6 + 100;
const int SMAX = 1e4 + 100;
const int NMAX = 110;

struct AC{
    int fr;
    vector <int> SF;
    AC *F[26], *fail;
    AC()
    {
        fr = 0; fail = 0;
        memset(F, 0, sizeof F);
    }
};

AC *T, *Q[SMAX * SMAX];
int N, st, dr, SOL[NMAX];
char A[AMAX], S[SMAX];

void Insert(char *p, int nr)
{
    int n = strlen(p); AC *nod = T;
    for(int i = 0; i < n; i++)
    {
        int next = p[i] - 'a';
        if(!nod->F[next]) nod->F[next] = new AC;
        nod = nod->F[next];
    }
    nod->SF.push_back(nr);
}

void BFS()
{
    AC *fpoz; T->fail = T;
    st = 1, dr = 1;
    Q[dr] = T;
    while(st <= dr)
    {
        AC *nod = Q[st]; st++;
        for(int i = 0; i < 26; i++)
            if(nod->F[i] != NULL)
            {
                for(fpoz = nod->fail; fpoz != T && fpoz->F[i] == NULL; fpoz = fpoz->fail);

                if(fpoz->F[i] != NULL && fpoz->F[i] != nod->F[i]) fpoz = fpoz->F[i];
                nod->F[i]->fail = fpoz;
                Q[++dr] = nod->F[i];
            }
    }
    T->fail = NULL;
}

void REV_BFS()
{
    AC *nod;
    while(dr)
    {
        nod = Q[dr]; dr--;
        if(nod->fail != NULL)
            nod->fail->fr += nod->fr;
        for(unsigned i = 0; i < nod->SF.size(); i++)
            SOL[nod->SF[i]] = nod->fr;
    }
}

int main()
{
    fin.getline(A, AMAX);
    fin >> N; fin.get(); T = new AC;
    for(int i = 1; i <= N; i++)
    {
        fin.getline(S, SMAX);
        Insert(S, i);
    }

    BFS();

    int n = strlen(A); AC *nod = T;
    for(int i = 0; i < n; i++)
    {
        int next = A[i] - 'a';
        for(; nod != T && nod->F[next] == NULL; nod = nod->fail);
        if(nod->F[next] != NULL) nod = nod->F[next];
        ++nod->fr;
    }

    REV_BFS();
    for(int i = 1; i <= N; i++)
        fout << SOL[i] << '\n';
    return 0;
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

const int SMAX = 2e6 + 100;

char A[SMAX], B[SMAX];
int N, M, sol, PI[SMAX];
vector <int> S;

void Build_PI()
{
    int q = 0;
    for(int i = 2; i <= N; i++)
    {
        while(q && A[q + 1] != A[i])
            q = PI[q];
        if(A[q + 1] == A[i]) q++;
        PI[i] = q;
    }
}

int main()
{
    fin.getline(A + 1, SMAX);
    fin.getline(B + 1, SMAX);
    N = strlen(A + 1), M = strlen(B + 1);

    Build_PI();

    int q = 0;
    for(int i = 1; i <= M; i++)
    {
        while(q && A[q + 1] != B[i])
            q = PI[q];
        if(A[q + 1] == B[i]) q++;
        if(q == N)
        {
            sol++;
            if(sol <= 1000)
                S.push_back(i - N);
        }
    }

    fout << sol << '\n';
    for(int i = 0; i < S.size(); i++)
        fout << S[i] << ' ';

    return 0;
}

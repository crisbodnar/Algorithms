#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("ciur.in");
ofstream fout("ciur.out");

const int NMAX = 2e6 + 10;

int N, cnt = 1;
bool P[NMAX];

int main()
{
    fin >> N;
    for(int i = 4; i <= N; i += 2)
        P[i] = 1;
    for(int i = 3; i <= N; i += 2)
        if(!P[i])
        {
            cnt++;
            for(int j = i + i; j <= N; j += i)
                P[j] = 1;
        }
    fout << cnt;
    return 0;
}

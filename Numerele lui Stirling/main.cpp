#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("stirling.in");
ofstream fout("stirling.out");

const int NMAX = 210;
const int MOD = 98999;

int T;
int s[NMAX][NMAX], S[NMAX][NMAX];

void Builds()
{
    //Stirling de speta I
    //Numarul permutarilor de n elemente cu exact m cicluri
    s[1][1] = 1;
    for(int i = 2; i <= 200; i++)
        for(int j = 1; j <= i; j++)
            s[i][j] = (s[i - 1][j - 1] - (i - 1) * s[i - 1][j]) % MOD;
}

void BuildS()
{
    //Stirling de speta a II - a
    //Numarul de posibilitati de a partitiona n elemnteme in m clase
    S[1][1] = 1;
    for(int i = 2; i <= 200; i++)
        for(int j = 1; j <= i; j++)
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;
}

int main()
{
    Builds();
    BuildS();
    fin >> T;
    while(T--)
    {
        int tip, x, y;
        fin >> tip >> x >> y;
        if(tip == 1) fout << s[x][y];
        else fout << S[x][y];
        fout << '\n';
    }
    return 0;
}

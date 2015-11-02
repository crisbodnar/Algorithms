#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("euclid2.in");
ofstream fout("euclid2.out");

int T, A, B;

int CMMDC(int X, int Y)
{
    if(!Y) return X;
    CMMDC(Y, X % Y);
}

int main()
{
    fin >> T;
    while(T--)
    {
        fin >> A >> B;
        fout << CMMDC(A, B) << '\n';
    }
    return 0;
}

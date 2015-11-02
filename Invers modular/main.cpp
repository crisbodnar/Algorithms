#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("inversmodular.in");
ofstream fout("inversmodular.out");

int A, N;

void Euclid(int A, int B, int &x, int &y)
{
    if(!B)
    {
        x = 1; y = 0;
        return;
    }
    int x0, y0;
    Euclid(B, A % B, x0, y0);
    x = y0;
    y = x0 - (A / B) * y0;
}

int main()
{
    fin >> A >> N;
    int x, y;
    Euclid(A, N, x, y);

    if(x < 0)
        x = N + x % N;
    fout<< x;
    return 0;
}

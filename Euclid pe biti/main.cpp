#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("euclid2.in");
ofstream fout("euclid2.out");

int T, A, B;

int CMMDC(int a, int b)
{
    if(a == b) return a;
    if(!a || !b) return a + b;

    if(~a & 1)
        if(~b & 1)
            return CMMDC(a >> 1, b >> 1) << 1;
        else
            return CMMDC(a >> 1, b);

    if(~b & 1)
        return CMMDC(a, b >> 1);

    if(a > b)
        return CMMDC((a-b) >> 1, b);
    return CMMDC((b - a) >> 1, a);

}

int main()
{
    fin >> T;
    while(T--)
    {
        fin >> A >> B;
        if(A < B) swap(A, B);
        fout << CMMDC(A, B) << '\n';
    }
    return 0;
}

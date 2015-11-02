#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int CMMDC(int a, int b, int &x, int &y)
{
    if(!b)
    {
        x = 1; y = 0;
        return a;
    }
    int xx, yy, d;
    d = CMMDC(b, a % b, xx, yy);
    x = yy;
    y = xx - (a / b) * yy;
    return d;
}

int main()
{
    int T; fin >> T;
    while(T--)
    {
        int a, b, c, d, x, y;
        fin >> a >> b >> c;
        d = CMMDC(a, b, x, y);

        if(c % d)
            fout << "0 0\n";
        else
            fout << x * (c / d) << ' ' << y * (c / d) << '\n';
    }
    return 0;
}

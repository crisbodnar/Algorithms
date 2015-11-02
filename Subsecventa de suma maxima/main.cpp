#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

ifstream fin("ssm.in");
ofstream fout("ssm.out");

const int NMAX = 6e6 + 100;

int N, st, dr, beg, sum = -1;

int main()
{
    fin >> N; int sol = INT_MIN;
    for(int i = 1; i <= N; i++)
    {
        int x; fin >> x;
        if(sum < 0)
            sum = x, st = i;
        else
            sum += x;
        if(sol < sum)
            sol = sum, beg = st, dr = i;
    }

    fout << sol << ' ' << beg << ' ' << dr;
    return 0;
}

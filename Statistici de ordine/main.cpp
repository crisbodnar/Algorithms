#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("sdo.in");
ofstream fout("sdo.out");

const int NMAX = 3e6 + 100;

int N, K, V[NMAX];

int main()
{
    fin >> N >> K;
    for(int i = 1; i <= N; i++)
        fin >> V[i];
    nth_element(V + 1, V + K, V + N + 1);
    fout << V[K];
    return 0;
}

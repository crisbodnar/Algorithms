//Implementare cu coada de prioritate

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

const int NMAX = 2e5 + 100;

int top, N, O[NMAX];
priority_queue <int, vector<int>, greater<int> > Heap;
priority_queue <int, vector<int>, greater<int> > Pop;

int main()
{
    fin >> N;
    while(N--)
    {
        int tip, a;
        fin >> tip;
        if(tip == 1)
        {
            fin >> a;
            O[++top] = a;
            Heap.push(a);
        }
        else if(tip == 2)
        {
            fin >> a;
            Pop.push(O[a]);
        }
        else
        {
            while(!Heap.empty() && !Pop.empty() && Heap.top() == Pop.top())
                Heap.pop(), Pop.pop();
            fout << Heap.top() << '\n';
        }
    }
    return 0;
}

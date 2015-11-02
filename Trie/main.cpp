#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

ifstream fin("trie.in");
ofstream fout("trie.out");

struct Trie{
    int fr, ap;
    Trie* f[26];
    Trie(){memset(f, 0, sizeof f); fr = ap = 0;}
};

Trie *T;

void Add(string s)
{
    Trie *x = T;
    for(int i = 0; i < s.size(); i++)
    {
        int newn = s[i] - 'a';
        if(!x->f[newn]) x->f[newn] = new Trie;
        x = x->f[newn]; x->ap++;
    }
    x->fr++;
}

void Erase(string s)
{
    Trie *x = T;
    for(int i = 0; i < s.size(); i++)
    {
        int newn = s[i] - 'a';
        x = x->f[newn]; x->ap--;
    }
    x->fr--;
}

int Freq(string s)
{
    Trie *x = T;
    for(int i = 0; i < s.size(); i++)
    {
        int newn = s[i] - 'a';
        if(x->f[newn] && x->f[newn]->ap)
            x = x->f[newn];
        else
            return 0;
    }
    return x->fr;
}

int Prefix(string s)
{
    Trie *x = T; int lg = 0;
    for(int i = 0; i < s.size(); i++)
    {
        int newn = s[i] - 'a';
        if(x->f[newn] && x->f[newn]->ap)
            x = x->f[newn];
        else
            return lg;
        lg++;
    }
    return lg;
}

int main()
{
    int tip; string s; T = new Trie;
    while(fin >> tip >> s)
    {
        if(!tip) Add(s); else
        if(tip == 1) Erase(s); else
        if(tip == 2) fout << Freq(s) << '\n'; else
        fout << Prefix(s) << '\n';
    }
    return 0;
}

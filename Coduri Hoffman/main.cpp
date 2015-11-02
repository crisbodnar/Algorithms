#include <queue>
#include <cstdio>

using namespace std;

#define f first
#define s second
#define cod1 (code << 1)
#define cod2 cod1 + 1

const int N = 1000010;

long long n, lgmin, vf, v[N*2], cod[N], lg[N];
vector < pair <int, int> > fiu(2*N);
queue <int> q1, q2;

void dfs(int nod, long long height, long long code)
{
    if(nod > n)
    {
        lgmin += v[nod];
        dfs(fiu[nod].f, height + 1, cod1);
        dfs(fiu[nod].s, height + 1, cod2);
    }
    else
    {
        lg[nod] = height;
        cod[nod] = code;
    }
}

int Extract_Min()
{
    int mini;
    if(q1.empty())
    {
        mini = q2.front(); q2.pop();
        return mini;
    }
    if(q2.empty())
    {
        mini = q1.front(); q1.pop();
        return mini;
    }
    if(v[q1.front()] < v[q2.front()])
    {
        mini = q1.front(); q1.pop();
        return mini;
    }
    mini = q2.front(); q2.pop();
    return mini;
}

int main()
{
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);

    scanf ("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &v[i]);
        q1.push(i);
    }
    int min1, min2; vf = n;
    while(q1.size() + q2.size() > 1)
    {
        min1 = Extract_Min();
        min2 = Extract_Min();
        v[++vf] = v[min1] + v[min2];
        fiu[vf].f = min1;
        fiu[vf].s = min2;
        q2.push(vf);
    }
    dfs(vf, 0, 0);
    printf("%lld\n", lgmin);
    for(int i=1; i<=n; i++)
        printf ("%lld %lld\n" , lg[i], cod[i]);
    return 0;
}

//ZOJ - 3197

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <math.h>
#include <map>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
#define up(i, j, k) for (int i = j; i < k; i++)
#define uup(i, j, k) for (int i = j; i >= k; i--)
#define mem(i, j) memset(i, j, sizeof i)
#define ll long long
#define mod(x) (x) % mod
#define sfi(i) scanf("%d", &i)
#define sfs(i) scanf("%s", i)
#define sfc(i) scanf("%c", &i)
#define sfd(i) scanf("%lf", &i)
#define sff(i) scanf("%f", &i)
#define sfl(i) scanf("%lld", &i)
#define whatis(i) cout << "This is:" << i << endl;
#define setflag() cout << "This is a flag!" << endl;

const int N = 1e6 + 5;
const int inf = 0x7fffffff;
const int mod = 1e9 + 7;
const double eps = 1e-11;
const double PI = acos(-1.0);
const int MAX = 5e3 + 10;

struct node
{
    int l, r;
    bool operator<(const node &a)
    {
        if (l == a.l)
            return r < a.r;
        return l < a.l;
    }
} p[MAX];
bool vis[MAX];
int main()
{
    int T;
    sfi(T);
    while (T--)
    {
        int n;
        sfi(n);
        up(i, 0, n)
        {
            sfi(p[i].l);
            sfi(p[i].r);
        }
        sort(p, p + n);
        int left = 1;
        int sum = 0;
        int t = 0;
        int flag = 0;
        while (left <= n)
        {
            int maxn = 0;
            up(i, t, n)
            {
                if (p[i].l <= left)
                {
                    maxn = max(maxn, p[i].r);
                    if (i == n - 1)
                    {
                        sum++;
                        flag = 1;
                    }
                }
                else
                {
                    t = i;
                    left = maxn + 1;
                    sum++;
                    break;
                }
            }
            if (flag)
                break;
        }
        printf("%d\n", sum);
    }
    return 0;
}
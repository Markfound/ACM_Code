#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
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
const int MAX = 1e6 + 5;

int n;
struct node
{
    double x, y;
    bool operator<(const node a) const
    {
        if (x == a.x)
            return y < a.y;
        return x < a.x;
    }
} p[MAX], temp[MAX];
bool com(const node a, const node b)
{
    return a.y < b.y;
}
double dis(const node a, const node b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double solve(int left, int right)
{
    if (left == right)
        return (double)inf;
    if (left + 1 == right)
        return dis(p[left], p[right]);
    int mid = (left + right) >> 1;
    double d1 = solve(left, mid);
    double d2 = solve(mid, right);
    double d = min(d1, d2);
    int res = 0;
    up(i, left, right + 1)
    {
        if (p[i].x >= p[mid].x - d && p[i].x <= p[mid].x + d)
        {
            temp[res].x = p[i].x;
            temp[res++].y = p[i].y;
        }
    }
    sort(temp, temp + res, com);
    up(i, 0, res)
    {
        for (int j = i + 1; j < res && temp[j].y - temp[i].y < d; j++)
        {
            d = min(d, dis(temp[i], temp[j]));
        }
    }
    return d;
}
int main()
{
    while (~sfi(n) && n)
    {
        up(i, 0, n)
        {
            sfd(p[i].x);
            sfd(p[i].y);
        }
        sort(p, p + n);
        double ss = solve(0, n - 1);
        printf("%.2lf\n", ss / 2);
    }
    return 0;
}
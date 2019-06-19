//HDU - 1255

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>
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
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const double PI = acos(-1.0);
const int MAX = 1e3 + 5;

struct Line
{
    double x, y1, y2;
    int f;
    void init(double x, double y1, double y2, int f)
    {
        this->f = f;
        this->x = x;
        this->y1 = y1;
        this->y2 = y2;
    }
    bool operator<(const Line xx)
    {
        return x < xx.x;
    }
} line[MAX << 1];

struct node
{
    double left, right;
    double once, more;
    int cover;
} p[MAX * 10];

double y[MAX << 1];

void Build_Tree(int l, int r, int x)
{
    p[x].left = y[l];
    p[x].right = y[r];
    p[x].once = p[x].cover = p[x].more = 0;
    if (r - l == 1)
    {
        p[x << 1].once = p[x << 1].more = p[x << 1].cover = 0;
        p[x << 1 | 1].cover = p[x << 1 | 1].once = p[x << 1 | 1].more = 0;
        return;
    }
    Build_Tree(l, (l + r) >> 1, x << 1);
    Build_Tree((l + r) >> 1, r, x << 1 | 1);
}
void Updata(int x)
{
    if (p[x].cover == 0)
    {
        p[x].once = p[x << 1].once + p[x << 1 | 1].once;
    }
    else
    {
        p[x].once = p[x].right - p[x].left;
    }
    if (p[x].cover == 0)
    {
        p[x].more = p[x << 1].more + p[x << 1 | 1].more;
    }
    else if (p[x].cover == 1)
    {
        p[x].more = p[x << 1].once + p[x << 1 | 1].once;
    }
    else
    {
        p[x].more = p[x].right - p[x].left;
    }
}
void Updata_Tree(int x, Line l)
{
    if (p[x].left == l.y1 && p[x].right == l.y2)
    {
        p[x].cover += l.f;
        Updata(x);
        return;
    }
    int t = x;
    t <<= 1;
    if (p[t].right > l.y1)
    {
        if (p[t].right > l.y2)
        {
            Updata_Tree(t, l);
        }
        else
        {
            Line l1 = l;
            l1.y2 = p[t].right;
            Updata_Tree(t, l1);
        }
    }
    t++;
    if (p[t].left < l.y2)
    {
        if (p[t].left < l.y1)
        {
            Updata_Tree(t, l);
        }
        else
        {
            Line l1 = l;
            l1.y1 = p[t].left;
            Updata_Tree(t, l1);
        }
    }
    Updata(x);
}
int main()
{
    int T;
    sfi(T);
    while (T--)
    {
        int n;
        sfi(n);
        double temp[MAX << 1];
        double x1, x2, y1, y2;
        int cnt = 0;
        up(i, 0, n)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            temp[cnt] = y1;
            line[cnt++].init(x1, y1, y2, 1);
            temp[cnt] = y2;
            line[cnt++].init(x2, y1, y2, -1);
        }
        sort(temp, temp + cnt);
        sort(line, line + cnt);
        int res = 0;
        y[res++] = temp[0];
        up(i, 1, cnt)
        {
            if (temp[i] == temp[i - 1])
                continue;
            y[res++] = temp[i];
        }
        Build_Tree(0, res - 1, 1);
        double sum = 0;
        up(i, 0, cnt - 1)
        {
            Updata_Tree(1, line[i]);
            sum += p[1].more * (line[i + 1].x - line[i].x);
        }
        printf("%.2lf\n", sum);
    }
    return 0;
}
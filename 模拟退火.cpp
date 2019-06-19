//HDU - 3644

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <fstream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;
#define ll long long
#define mem(i, j) memset(i, j, sizeof i)
#define up(i, j, k) for (int i = j; i < k; i++)
#define uup(i, j, k) for (int i = j; i >= k; i--)
#define mod(x) (x) % mod
#define sfi(i) scanf("%d", &i)
#define sfs(i) scanf("%s", i)
#define sfc(i) scanf("%c", &i)
#define sfl(i) scanf("%lld", &i)
#define sfd(i) scanf("%lf", &i)
#define sff(i) scanf("%f", &i)
#define wt(a) cout << "This is:" << a << endl
#define sf() cout << "This is a flag" << endl

const int N = 1010;
const double pi = 4 * atan(1.0);
const ll llinf = 0x7fffffffffffffff;
const double inf = 9999999999;
const int mod = 998244353;
const double eps = 1e-5;
const int MAX = 1e2 + 15;
int n;
struct node
{
    double x, y;
} p[MAX], ans, temp;

double sqr(double x)
{
    return x * x;
}
int epss(double x)
{
    if (fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}
double dis(const node a, const node b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double cross(node k, node aa, node bb)
{
    return (k.x - aa.x) * (k.y - bb.y) - (k.y - aa.y) * (k.x - bb.x);
}
double get_dis(const node l1, const node l2, const node aa)
{
    double dis1 = dis(aa, l1);
    double dis2 = dis(aa, l2);
    double dis3 = dis(l1, l2);
    if (epss(sqr(dis1) + sqr(dis3) - sqr(dis2)) < 0)
    {
        return dis1;
    }
    if (epss(sqr(dis2) + sqr(dis3) - sqr(dis1)) < 0)
    {
        return dis2;
    }
    else
    {
        return fabs(cross(aa, l1, l2) / dis3);
    }
}
double get_min(const node aa)
{
    double minn = inf;
    up(i, 0, n)
    {
        minn = min(minn, get_dis(p[i], p[i + 1], aa));
    }
    return minn;
}

bool get_inside(const node aa)
{
    int cnt = 0;
    up(i, 0, n)
    {
        double kk = p[i].y - p[i + 1].y;
        if (epss(kk) == 0)
            continue;
        if (aa.y < min(p[i].y, p[i + 1].y))
            continue;
        if (aa.y > max(p[i].y, p[i + 1].y))
            continue;
        double P = (aa.y - p[i + 1].y) * (p[i].x - p[i + 1].x) / (p[i].y - p[i + 1].y) + p[i + 1].x;
        if (epss(P - aa.x) >= 0)
            cnt++;
    }
    return cnt % 2;
}
double maxx, maxy, minx, miny;
double R;
int di[8][2] = {1, 1, -1, -1, 1, 0, 0, 1, 0, -1, -1, 0, 1, -1, -1, 1};
void solve()
{
    srand((unsigned int)time(NULL));
    ans.x = (p[0].x + p[1].x) / 2;
    ans.y = (p[0].y + p[1].y) / 2;
    double ansdis = get_min(ans);
    double T = max(maxx, maxy);
    double delta = 0.9;
    double Tmin = 1e-3;
    while (T > Tmin)
    {
        up(i, 0, 30)
        {
            up(j, 0, 8)
            {
                temp.x = ans.x + rand() * T * 1.0 / RAND_MAX * di[j][0];
                temp.y = ans.y + rand() * T * 1.0 / RAND_MAX * di[j][1];
                if (get_inside(temp))
                {
                    double dis1 = get_min(temp);
                    if (dis1 > ansdis)
                    {
                        ansdis = dis1;
                        ans = temp;
                    }
                }
            }
        }

        T *= delta;
    }
    if (epss(ansdis - R) >= 0)
        printf("Yes\n");
    else
        printf("No\n");
}
int main()
{
    while (~sfi(n) && n)
    {
        maxx = 0, maxy = 0, minx = inf, miny = inf;
        up(i, 0, n)
        {
            sfd(p[i].x);
            sfd(p[i].y);
            maxx = max(maxx, p[i].x);
            minx = min(minx, p[i].x);
            maxy = max(maxy, p[i].y);
            miny = min(miny, p[i].y);
        }
        p[n] = p[0];
        sfd(R);
        solve();
    }
    return 0;
}
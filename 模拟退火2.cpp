//POJ - 2420

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
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-10;
const int MAX = 1e2 + 10;

//模拟退火  求全局最优问题

struct node
{
    double x, y;
} p[MAX], temp, res, ans;
int n;
double sqr(double x)
{
    return x * x;
}
double dis(const node a)
{
    double sum = 0;
    up(i, 0, n)
    {
        sum += sqrt(sqr(a.x - p[i].x) + sqr(a.y - p[i].y));
    }
    return sum;
}

double delta = 0.99; //退火速度

void solve()
{
    double T = 10000; //初始温度
    srand((unsigned)&T);
    double Tmin = 1e-8; //下限温度
    ans = p[0];
    while (T > Tmin)
    {
        temp.x = ans.x + (rand() & 1 ? 1 : -1) * (double)rand() * T / (double)RAND_MAX;
        temp.y = ans.y + (rand() & 1 ? 1 : -1) * (double)rand() * T / (double)RAND_MAX;
        double dis1 = dis(temp);
        double dis2 = dis(ans);
        if (dis1 < dis2)
        {
            ans = temp;
        }
        else
        {
            double P = exp((dis2 - dis1) / T * rand());
            if (P > rand() * 1.0 / RAND_MAX)
            {
                ans = temp;
            }
        }
        T *= delta;
    }
}

int main()
{
    while (~sfi(n))
    {
        up(i, 0, n)
        {
            sfd(p[i].x);
            sfd(p[i].y);
        }
        solve();
        printf("%.0f\n", dis(ans));
    }
    return 0;
}
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
const ll llinf = 0x7fffffffffffffff;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const double eps = 1e-8;
const int MAX = 1e6 + 10;
int arr[5][5000];
int sum[4000 * 4000 + 5];
int main()
{
    int n;
    while (~sfi(n))
    {
        up(i, 0, n)
        {
            up(j, 0, 4)
            {
                sfi(arr[j][i]);
            }
        }
        int t;
        int k = 0;
        up(i, 0, n)
        {
            up(j, 0, n)
            {
                t = arr[0][i] + arr[1][j];
                sum[k++] = -1 * t;
            }
        }
        sort(sum, sum + k);
        int ss = 0;
        up(i, 0, n)
        {
            up(j, 0, n)
            {
                t = arr[2][i] + arr[3][j];
                ss += (upper_bound(sum, sum + k, t) - lower_bound(sum, sum + k, t));
            }
        }
        printf("%d\n", ss);
    }
    return 0;
}
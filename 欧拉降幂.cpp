//FZU - 1759
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
#define mem(i, j) memset(i, j, sizeof i)
#define up(i, j, k) for (int i = j; i < k; i++)
#define uup(i, j, k) for (int i = j; i >= k; i--)
#define ll long long
#define mod(x) x % mod
#define sfi(i) scanf("%d", &i)
#define sfl(i) scanf("%lld", &i)
#define sfd(i) scanf("%lf", &i)
#define sfs(i) scanf("%s", i)
#define sfc(i) scanf("%c", &i)
#define sf() cout << "This is a flag!" << endl;

const int mod = 1e9 + 7;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;
const ll INF = 0x7f7f7f7f7f7f7f7f;
const int MAX = 1e6 + 5;
ll a, c;
char b[MAX];

ll get_mod(ll xx)
{
    ll sum = 0;
    int len = strlen(b);
    up(i, 0, len)
    {
        sum = sum * 10 + (b[i] - '0');
        sum %= xx;
    }
    return sum % xx;
}

ll phi(ll xx)
{
    ll ans = xx;
    for (int i = 2; i * i <= xx; i++)
    {
        if (xx % i == 0)
        {
            ans = ans / i * (i - 1);
            while (xx % i == 0)
                xx /= i;
        }
    }
    if (xx > 1)
        ans = ans / xx * (xx - 1);
    return ans;
}

ll qpow(ll a, ll n, ll m)
{
    ll res = 1;
    a %= m;
    while (n)
    {
        if (n & 1)
        {
            res *= a;
            res %= m;
        }
        a *= a;
        a %= m;
        n >>= 1;
    }
    return res % m;
}
int main()
{
    while (~sfl(a))
    {
        sfs(b);
        sfl(c);
        ll x = phi(c);
        ll xx = get_mod(x);
        xx += x;
        printf("%lld\n", qpow(a, xx, c) % c);
    }
    return 0;
}
//若一个问题的结论是通过推线性递推式来解，考虑到实际的情况，可以用BM算法的模板，先输入项数再依次输入项，项越多越准确

#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = int(a); i < int(b); ++i)

#define mem(a, p) memset(a, p, sizeof(a))

#define MAXN 1005

struct BM
{
    int n{};

    vector<double> ps[MAXN];
    int pn{}, fail[MAXN]{};
    double delta[MAXN]{};

    void Solve(const double *x, int n)
    {
        pn = 0;
        mem(fail, 0);
        mem(delta, 0);
        ps[0].clear();
        rep(i, 1, n + 1)
        {
            double dt = -x[i];
            rep(j, 0, ps[pn].size())
                dt += x[i - j - 1] * ps[pn][j];
            delta[i] = dt;
            if (fabs(dt) <= 1e-8)
                continue;
            fail[pn] = i;
            if (!pn)
            {
                ps[++pn].resize(1);
                continue;
            }
            vector<double> &ls = ps[pn - 1];
            double k = -dt / delta[fail[pn - 1]];
            vector<double> cur;
            cur.resize(i - fail[pn - 1] - 1);
            cur.push_back(-k);
            rep(j, 0, ls.size()) cur.push_back(ls[j] * k);
            if (cur.size() < ps[pn].size())
                cur.resize(ps[pn].size());
            rep(j, 0, ps[pn].size()) cur[j] += ps[pn][j];
            ps[++pn] = cur;
        }
    }

    void print()
    {
        cout << setiosflags(ios::fixed) << setprecision(10);
        for (int i = 0; i < ps[pn].size(); ++i)
        {
            cout << ps[pn][i] << " ";
        }
        cout << endl;
    }
} B;

double x[MAXN];

int main()
{
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++i)
        {
            cin >> x[i];
        }
        B.Solve(x, n);
        B.print();
    }
}

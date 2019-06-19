// hdu -- Ch’s gift

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

struct Node
{
    ll cnt;
    int ls, rs;
} tree[N << 5];
int tot, rt[N];

int m, c[N], d[N], sz[N], fa[N], top[N], dep[N], son[N];

vector<int> G[N];

void insert(int &i, int l, int r, int x)
{
    tree[++tot] = tree[i], i = tot, tree[tot].cnt += d[x];
    if (l == r)
        return;
    int mid = (l + r) / 2;
    if (x <= mid)
        insert(tree[i].ls, l, mid, x);
    else
        insert(tree[i].rs, mid + 1, r, x);
}

ll query(int L, int R, int i, int l, int r)
{
    if (R < l || r < L)
        return 0;
    if (L <= l && r <= R)
        return tree[i].cnt;
    int mid = (l + r) / 2;
    return query(L, R, tree[i].ls, l, mid) + query(L, R, tree[i].rs, mid + 1, r);
}

void getSz(int u, int f, int d)
{
    sz[u] = 1, fa[u] = f, dep[u] = d;
    for (auto &v : G[u])
    {
        if (v != f)
        {
            getSz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]])
                son[u] = v;
        }
    }
}

void dfs(int u, int t)
{
    top[u] = t, rt[u] = rt[fa[u]];
    insert(rt[u], 1, m, c[u]);
    if (son[u])
        dfs(son[u], t);
    for (auto &v : G[u])
    {
        if (v != fa[u] && v != son[u])
            dfs(v, v);
    }
}

int lca(int u, int v)
{
    for (; top[u] ^ top[v]; u = fa[top[u]])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
    }
    return (dep[u] < dep[v]) ? u : v;
}

ll getAns(int u, int v, int a, int b)
{
    a = lower_bound(d + 1, d + 1 + m, a) - d;
    b = upper_bound(d + 1, d + 1 + m, b) - d - 1;
    int l = lca(u, v), f = fa[l];
    return query(a, b, rt[u], 1, m) + query(a, b, rt[v], 1, m) - query(a, b, rt[l], 1, m) - query(a, b, rt[f], 1, m);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i], d[i] = c[i];
    }
    sort(d + 1, d + 1 + n);
    m = unique(d + 1, d + 1 + n) - d - 1;
    for (int i = 1; i <= n; i++)
    {
        c[i] = lower_bound(d + 1, d + 1 + m, c[i]) - d;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    getSz(1, 0, 1), dfs(1, 1);
    while (q--)
    {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        cout << getAns(u, v, a, b) << "\n";
    }
}

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define ppb pop_back
using namespace std;
typedef long long ll;
const int mod = 998244353;
int n, m, k, t;
string s;
vector<int> a(1000005);
vector<vector<int>> edge(1000005);
double g[205][205], ans;
double f[205][205], eps = 1e-10;
bool gauss()
{
    for (int now = 1; now <= n; now++) {
        int tmp1 = 0;
        double tmp2 = -1e100;
        int sign = 1;
        for (int i = now; i <= n; i++)
            if (fabs(f[i][now]) > tmp2)
                tmp1 = i, tmp2 = fabs(f[i][now]),
                sign = f[i][now] < 0 ? -1 : 1;
        if (tmp2 < eps)
            return 0;
        for (int i = now; i <= n + 1; i++)
            f[tmp1][i] /= tmp2 * sign;
        for (int i = now; i <= n + 1; i++)
            tmp2 = f[now][i], f[now][i] = f[tmp1][i], f[tmp1][i] = tmp2;
        for (int i = 1; i <= n; i++)
            if (i != now && f[i][now] != 0) {
                for (int j = now + 1; j <= n + 1; j++)
                    f[i][j] -= f[i][now] * f[now][j];
                f[i][now] = 0;
            }
    }
    return 1;
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        double w;
        scanf("%d %d %lf", &u, &v, &w);
        g[u][v] += 1.0 / w;
        g[v][u] += 1.0 / w;
    }
    for (int i = 2; i < n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] += g[i][j], f[i][i] -= g[i][j];
    f[1][1] = 1, f[1][n] = -1, f[1][n + 1] = 1;
    for (int i = 1; i <= n; i++)
        f[n][i] = 1;
    gauss();
    for (int i = 1; i <= n; i++)
        ans += (f[1][n + 1] - f[i][n + 1]) * g[1][i];
    printf("%.2lf", 1.0 / ans);
    return 0;
}

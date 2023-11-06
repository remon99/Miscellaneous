#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
bool vis[N];

bool dfs(int vertex, int par)
{
    vis[vertex] = true;
    for (int child : g[vertex])
    {
        if (!vis[child])
        {
            if (dfs(child, vertex))
                return true;
        }
        else if (child != par)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int n, m;
    bool ans = false;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int v1, v2;
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!vis[i])
        {
            ans = dfs(i, -1);
            if (ans)
            {
                cout << 1 << endl;
                return 0;
            }
        }
    }
    cout << 0 << endl;
    return 0;
}

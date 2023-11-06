#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
bool vis[N];
bool recs[N];

bool dfs(int vertex)
{
    vis[vertex] = true;
    recs[vertex]=true;
    for (int child : g[vertex])
    {
        if (!vis[child])
        {
            if (dfs(child))
                return true;
        }
        else if (recs[child])
        {
            return true;
        }
    }
    recs[vertex]=false;
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
        //g[v2].push_back(v1);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!vis[i])
        {
            ans = dfs(i);
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

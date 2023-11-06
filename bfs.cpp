#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> graph1[N];

bool vis[N];

int level[N];

void bfs(int source)
{
    queue<int> q;
    q.push(source);
    vis[source] = true;
    while (!q.empty())
    {
        int cur_v = q.front();
        q.pop();
        cout << cur_v << " ";
        for (int child : graph1[cur_v])
        {
            if (!vis[child])
            {
                q.push(child);
                vis[child] = true;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int v1, v2;
        cin >> v1 >> v2;
        /* graph[v1][v2] = 1;
        graph[v2][v1] = 1; */
        graph1[v1].push_back(v2);
        graph1[v2].push_back(v1);
    }

    bfs(1);
    cout << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << i << " " << level[i] << endl;
    }

    return 0;
}
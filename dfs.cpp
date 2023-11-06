#include <bits/stdc++.h>
using namespace std;
#define pys cout << "YES" << endl
#define pyn cout << "NO" << endl
#define loop(i, n) for (int i = 0; i < n; ++i)
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define nl cout << endl
typedef vector<int> vi;
typedef long long ll;
const int N = 1e5 + 10;
//int graph[N][N];
vector<int> graph1[N];
bool vis[N];
void dfs(int vertex){
    //cout<<vertex<<endl;
    vis[vertex]=true;
    for(int child : graph1[vertex]){
        
        if(vis[child]) continue;
        cout<<vertex<<" "<<child<<endl;
        dfs(child);
    }
    
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

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
    dfs(1);
    return 0;
}

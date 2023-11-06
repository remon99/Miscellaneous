#include<bits/stdc++.h>
using namespace std;
#define pys cout<<"YES"<<endl
#define pyn cout<<"NO"<<endl
#define loop(i,n) for(int i=0;i<n;++i)
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define nl cout<<endl 
typedef vector<int> vi;
typedef long long ll;
const int N=1e5+10;
const int INF=1e9+10;
int n=4,m=5;
vector<pair<int,int>>g[N];
vector<int> wt(n+1, INF);
vector<bool>vis(n+1,false);

int extractMin(vector<int> &wt) {
    int minWeight = INT_MAX, idx = -1;
    for (int i = 1; i <= n; i++) {
        if (wt[i] < minWeight && vis[i]==false) {
            minWeight = wt[i];
            idx = i;
        }
    }
    return idx;
}

void findmst(int source) {
    
    vector<int> parent(n+1);
  
    parent[source] = -1;
    wt[source] = 0;
    for (int i = 1; i <= n-1; ++i) {
        int U = extractMin(wt);
        vis[U] = true;
        for (const auto neighbor : g[U]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (vis[v]==false && weight < wt[v]) {
                parent[v] = U;
                wt[v] = weight;
                
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        cout << parent[i] << " " << i << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 1; i <= m; i++) {
        int x, y, wt;
        cin >> x >> y >> wt;
        g[x].push_back({y, wt});
        g[y].push_back({x, wt});
    }

    findmst(1);

    return 0;
}


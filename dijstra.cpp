#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<pair<int, int>> g[N];
const int INF = 1e9 + 10;

void dij(int source){
    vector<int>vis(N,0);
    vector<int>dist(N,INF);

    set<pair<int,int>>st;
    st.insert({0,source});
    dist[source]=0;
    while(st.size()>0){
        auto node= *st.begin();
        int v=node.second;
        int v_dist=node.first;
        //cout<<v_dist<<endl;
        st.erase(st.begin());
        if(vis[v]) continue;;
        vis[v]=1;
        for(auto child : g[v]){
            int child_v=child.first;
            int child_wt=child.second;
            if(dist[v]+child_wt<dist[child_v]){
                dist[child_v]=dist[v]+child_wt;
                st.insert({dist[child_v],child_v});
            }
        }
    }
   for(int i=0;i<=6;i++){
    cout<<dist[i]<<endl;
   }
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int x, y, wt;
        cin >> x >> y >> wt;
        g[x].push_back({y, wt});
        
    }
    dij(1);
}
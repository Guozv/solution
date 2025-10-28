#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
inline void solve()
{
    int n,m;cin>>n>>m;
    vector<vector<pair<int,int> > >e(n+1);
    vi d(n+1);
    for(int i=1,u,v;i<=m;i++)
    {
        cin>>u>>v;
        d[u]++,d[v]++;
        e[u].emplace_back(v,i);
        e[v].emplace_back(u,i);
    }
    vi ve;
    for(int i=1;i<=n;i++)if(d[i]&1)ve.emplace_back(i);
    int id=m;
    for(int i=0;i<ve.size();i+=2)
    {
        id++;
        e[ve[i]].emplace_back(ve[i+1],id);
        e[ve[i+1]].emplace_back(ve[i],id);
    }
    vector<bool>vis(n+1),del(id+1);
    vector<pair<int,int> >lp;
    int tt=0;
    vi c(id+1);
 //   cerr<<ve.size()<<endl;
    function<void(int,int)>dfs=[&](int u,int pre)->void
    {
        vis[u]=1;
      
        while(!e[u].empty())
        {
            auto [v,id]=e[u].back();e[u].pop_back();
            if(id==pre||del[id])continue;
            del[id]=1;
            lp.emplace_back(v,id);
            if(vis[v])
            {
             //   cerr<<u<<" "<<v<<endl;
                tt++;
                for(auto [p,i]:lp)vis[p]=0,c[i]=tt;
                lp.clear();
            }
            dfs(v,id);
            return;
        }
        vis[u]=0;
    };
    for(int i=1;i<=n;i++)dfs(i,-1);
    for(int i=1;i<=m;i++)cout<<c[i]<<' ';cout<<'\n';
}
int main()
{
    int T;cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
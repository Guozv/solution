    #include <bits/stdc++.h>

    using namespace std;
    const int MAXN=5e5+10;
    using vi=vector<int>;
    using vii =vector<vi>;
    struct BIT:vi
    {
        BIT(int n):vi(n){}
        inline void add(int x,int k){for(;x<(int)size();x+=x&-x)(*this)[x]+=k;}
        inline int ask(int x)
        {
            if(x<=0)return 0;
            int ans=0;
            for(;x;x-=x&-x)ans+=(*this)[x];
            return ans;
        }
        inline int ask(int l,int r){return ask(r)-ask(l-1);}
        inline void add(int l,int r,int k)
        {
            add(l,k),add(r+1,-k);
        }
    };
    // int root,tot;
    //     int ls[MAXN<<2],rs[MAXN<<2];
    // int tag[MAXN<<2],sum[MAXN<<2];
    // inline void New(int &now){if(!now){now=++tot;}}
    // void ins(int &now,int l,int r,int L,int R, int k){
    //     New(now);
    //     if(L<=l&&r<=R) {sum[now]=k;tag[now]=k;return;}
    //     pd(now);
    //     if(L<=mid)ins(ls[now],l,mid,L,R,k);
    //     if(R>mid)ins(rs[now],mid+1,R)
    // }
    void work() {
        vi ve;
        int n,q;cin>>n>>q;
        vi x1(n+1),x2(n+1),y1(n+1),y2(n+1);
        map<int,vi>mp;
        for(int i=1;i<=n;i++)cin>>x1[i]>>y1[i]>>x2[i]>>y2[i],mp[x1[i]].emplace_back(i),mp[x2[i]+1].emplace_back(-i);
    /* vi v1,v2;
        for(int i=1;i<=n;i++)v1.emplace_back(x1[i]),v1.emplace_back(x2[i]),v1.emplace_back(x2[i]+1);
        for(int i=1;i<=n;i++)v2.emplace_back(y1[i]),v2.emplace_back(y2[i]),v2.emplace_back(y2[i]+1);
        sort(v1.begin(),v1.end());v1.erase(unique(v1.begin(),v1.end()),v1.end());
        sort(v2.begin(),v2.end());v2.erase(unique(v2.begin(),v2.end()),v2.end());

        auto get1=[&](int x){return lower_bound(v1.begin(),v1.end(),x)-v1.begin()+1;};
        auto get2=[&](int x){return lower_bound(v2.begin(),v2.end(),x)-v2.begin()+1;};
        cerr<<endl;
        for(int i=1;i<=n;i++)
        {
            x1[i]=get1(x1[i]),x2[i]=get1(x2[i]);
            y1[i]=get2(y1[i]),y2[i]=get2(y2[i]);
            cerr<<x1[i]<<' '<<y1[i]<<' '<<x2[i]<<' '<<y2[i]<<endl;
        }*/
        set<pair<int,int> >s;
        //s.insert({2e9,0});

        vi fa(n+1,0);
        vii e(n+1);
        s.insert({0,0});
        s.insert({1e9,0});
        for(auto& [p,ve]:mp)
        {
            sort(ve.begin(),ve.end(),[&](int x,int y)->bool{
                {
                    if(x<0&&y>0)return 1;
                    if(x>0&&y<0)return 0;
                    x=abs(x),y=abs(y);
                    return y1[x]==y1[y]&&y2[x]>y2[y]||y1[x]<y1[y];
                }
                });
            for(auto i:ve)
            {
                if(i<0)
                {
                    i=-i;
                    s.erase({y1[i],i});
                    s.erase({y2[i],fa[i]});
                }
                else
                {
                    auto ii=s.lower_bound({y1[i],i});
                    ii--;
                    fa[i]=ii->second;
                    s.insert({y1[i],i});
                    s.insert({y2[i],fa[i]});
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
        //  cerr<<fa[i]<<' ';
            e[fa[i]].emplace_back(i);
        }
    // cerr<<endl;
        vi dfn(n+1),top(n+1),siz(n+1),son(n+1),d(n+1);
        int tt=0;
        int K=__lg(n+1);
        vii F(K+1,vi(n+1));
        function<void(int)>dfs=[&](int u)->void
        {
            siz[u]=1;
            F[0][u]=fa[u];
            for(int i=1;i<=K;i++)F[i][u]=F[i-1][F[i-1][u]];
            for(auto v:e[u])
            {
                d[v]=d[u]+1;
                dfs(v);siz[u]+=siz[v];
                if(son[u]==0||siz[son[u]]<siz[v])son[u]=v;
            }
        };
        function<void(int,int)>pf=[&](int u,int tp)->void
        {
          // cerr<<u<<" "<<tt<<endl;
            dfn[u]=++tt;top[u]=tp;
            if(son[u])pf(son[u],tp);
            for(auto&v:e[u])if(v!=fa[u] && v!=son[u])pf(v,v);
        };
        vi maxd(n+1);
        dfs(0),pf(0,0);
        BIT t(n+3),t2(n+3);
        vi a(n+1);
        while(q--)
        {
            char c;int x;cin>>c>>x;
         //  cerr<<c<<' '<<x<<endl;
            if(c=='^')
            {
                int u=x;
                
                if(a[x])
                {
                    for(int i=K;~i;i--)if(t2.ask(dfn[F[i][u]],dfn[F[i][u]]+siz[F[i][u]]-1)==1)u=F[i][u];
                    //cerr<<cnt<<endl;
                    if(t2.ask(dfn[u],dfn[u]+siz[u]-1)==1)t.add(d[u]+1,d[x]+1,-1);
                    t2.add(dfn[x],-1);
                }
                else
                {
                    for(int i=K;~i;i--)if(!t2.ask(dfn[F[i][u]],dfn[F[i][u]]+siz[F[i][u]]-1))u=F[i][u];
                // cerr<<"!\n";
                    if(!t2.ask(dfn[u],dfn[u]+siz[u]-1))t.add(d[u]+1,d[x]+1,1);
                    t2.add(dfn[x],1);
                }
                a[x]^=1;
            
            }
            else
            {
                int k=x;
            // cerr<<k<<endl;
                cout<<t.ask(k+2)<<'\n';
            }
            
        }
    }

    signed main() {
        ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
        int _ = 1;
    // cin >> _;
        while (_--) work();
        return 0;
    }
    /*
    5 11
    315504722 82606748 885294760 775862194
    684326969 329797278 749547220 521704944
    644794176 126359876 873521124 650251937
    169924836 75846632 173413889 82606748
    305676433 75846632 912197686 958531132
    ? 1
    ? 3
    ^ 1
    ^ 2
    ^ 5
    ? 1
    ^ 1
    ^ 5
    ^ 5
    ? 3
    ? 0

    */
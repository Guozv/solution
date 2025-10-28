#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
using namespace std;
template<typename T>
inline bool cmax(T&x,const T& y){return x<y?x=y,1:0;}
template<typename T>
inline bool cmin(T&x,const T& y){return y<x?x=y,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<vector<int> > vii; 
const int mod=998244353;
inline void MOD(int&x){x-=mod,x+=x>>31&mod;}
inline void MOD(ll& x){x-=mod,x+=x>>63&mod;}
inline int add(int x,int y){MOD(x+=y);return x;}
inline int mul(int x,int y){return 1ll*x*y%mod;}
template<typename ... A>inline int mul(const int& x,const A&... p){return 1ll*x*mul(p...)%mod;}
inline ll ksm(ll a,ll p=mod-2){ll ans=1;for(;p;p>>=1,a=a*a%mod)if(p&1)ans=ans*a%mod;return ans;}
typedef long double LD;
const int MAXN=2e5+10;
struct
{
    int l,r;
    int cnt;
    ll sum;
}t[MAXN*30];
int tt;
#define ls t[p].l
#define rs t[p].r
void update(int& p,int l,int r,int qq,int k)
{
    if(!p)p=++tt;
    t[p].cnt+=k,t[p].sum+=k*qq;
    if(l==r)return;
    int mid=(l+r)>>1;
    if(qq<=mid) update(ls,l,mid,qq,k);
    else update(rs,mid+1,r,qq,k);
}
ll ask(int p,int l,int r,int k)
{
    if(!p||!k)return 0;
    if(l==r)return 1ll*l*min(k,t[p].cnt);
    int mid=(l+r)>>1;
    if(t[rs].cnt<k)return ask(ls,l,mid,k-t[rs].cnt)+t[rs].sum;
    else return ask(rs,mid+1,r,k);
}
int a[MAXN],rt;
vi e[MAXN];
const int N=1e9+1;
ll ans=0;
void dfs(int u,int fa,int cnt,ll sum)
{
    update(rt,0,N,a[u],-1);
    if(cnt<=0)return;
    sum-=a[u];
    if(e[u].size()==1)
    {
        //cerr<<t[1].cnt<<endl;
        cmax(ans,sum+ask(rt,0,N,cnt));
    }
   
    for(auto v:e[u])if(v!=fa)
    { 
        dfs(v,u,cnt+1,sum);
        sum+=a[v];
        cnt--;
    }
    for(auto v:e[u])if(v!=fa) update(rt,0,N,a[v],1);
}
inline void solve()
{
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1,u,v;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
    for(int u=1;u<=n;u++)sort(e[u].begin(),e[u].end(),[&](int x,int y){return a[x]>a[y];});
    for(int i=1;i<=n;i++)update(rt,0,N,a[i],1);
    ans=a[1];
    dfs(1,0,2,0);
    cout<<ans;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
} 
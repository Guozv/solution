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
const int mod=1e9+7;
inline void MOD(int&x){x-=mod,x+=x>>31&mod;}
inline void MOD(ll& x){x-=mod,x+=x>>63&mod;}
inline int add(int x,int y){MOD(x+=y);return x;}
inline int mul(int x,int y){return 1ll*x*y%mod;}
template<typename ... A>inline int mul(const int& x,const A&... p){return 1ll*x*mul(p...)%mod;}
inline ll ksm(ll a,ll p=mod-2){ll ans=1;for(;p;p>>=1,a=a*a%mod)if(p&1)ans=ans*a%mod;return ans;}
typedef long double LD;
const int MAXN=2e5+10;
inline void solve()
{
    int n1,n2,m,k;cin>>n1>>n2>>m>>k;
    vi a(k),b(k);
    vi ve;
    for(int i=0;i<k;i++)cin>>a[i]>>b[i],a[i]--,b[i]--,ve.emplace_back(a[i]),ve.emplace_back(b[i]);
    sort(ve.begin(),ve.end()),ve.erase(unique(ve.begin(),ve.end()),ve.end());
    vi st(m);
    for(int i=0;i<k;i++)
    {
        a[i]=lower_bound(ve.begin(),ve.end(),a[i])-ve.begin();
        b[i]=lower_bound(ve.begin(),ve.end(),b[i])-ve.begin();
        st[a[i]]|=1<<b[i];
        st[b[i]]|=1<<a[i];
    }
    int n=ve.size();
    vi f1(m+1),f2(m+1);
    f1[0]=1;

    for(int i=1,j=(n1+=m-n-1);i<=m;i++,j--)
    {
        f1[i]=mul(f1[i-1],j,(int)ksm(i));
    }
    f2[0]=1;

    for(int i=1,j=(n2+=m-n-1);i<=m;i++,j--)
    {
        f2[i]=mul(f2[i-1],j,(int)ksm(i));
    }
    int S=(1<<n)-1;
    vi F(S+1),g(S+1);
    vector<bool>vis(S+1);
    F[0]=f1[m-1];
    vis[0]=1;
    for(int i=1;i<S;i++)
    {
        int j=__lg(i&-i);
        int p=i^(1<<j);
        if(vis[p]&&!(g[p]>>j&1)&&!(st[j]>>j&1))
        {
            vis[i]=1;
            g[i]=g[p]|st[j];
        }
        if(vis[i])
        {
            F[i]=f1[m-1-__builtin_popcount(i)];
        }
    }
    for(int i=0;i<n;i++)
        for(int s=0;s<=S;s++)if(s>>i&1)
        {
            MOD(F[s]+=F[s^(1<<i)]);
        }

    ll ans=0;
    for(int s=0;s<S;s++)if(vis[s])
    {
        ans+=mul(f2[m-1-__builtin_popcount(s)],F[S^s]);
    }
    cout<<ans%mod<<'\n';
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
} 
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
const int MAXN=1e6+10;
int fa[MAXN];
vi e[MAXN];
const int K=20;
int F[K+1][MAXN],d[MAXN];
int vis[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,m;cin>>n>>m;
	for(int i=2;i<=n;i++)cin>>fa[i],d[i]=d[fa[i]]+1,F[0][i]=fa[i];
	for(int i=1;i<=K;i++)
		for(int u=1;u<=n;u++)
			F[i][u]=F[i-1][F[i-1][u]];
	memset(vis,-1,sizeof(vis));
	vis[0]=0;
	vis[1]=1;
	for(int i=1;i<=m;i++)
	{
		int u,l,r;cin>>u>>l>>r;
		if(~  vis[u])
		{
			
			cout<<max(vis[u],l)<<endl;
			return 0;
		}
		int p=u;
		//cerr<<F[0][p]<<endl;
		for(int j=K;~j;j--)if(vis[F[j][p]]==-1)p=F[j][p];
		//cerr<<p<<endl;
		int dt=d[u]-d[p]+1;
		if(dt<=r-l+1)
		{
		//	cerr<<"!\n";
			cout<<dt+l-1<<endl;
			return 0;
		}
	//	cerr<<p<<endl;
		p=u;

		for(int j=K;~j;j--)if((dt-(r-l+1))>>j&1)p=F[j][p];
	//	cerr<<p<<endl;
		while(vis[p]==-1)vis[p]=r--,p=fa[p];
	//	for(int j=1;j<=n;j++)cerr<<vis[j]<<' ';cerr<<endl;
	}
	cout<<-1;
	return 0;
} 
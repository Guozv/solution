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
inline void solve()
{
	int n;cin>>n;
	vector<ll> a(n+1);
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	auto cost=[&](int l,int r,int m){return 1ll*min(a[m]-a[l-1],a[r]-a[m])*(__lg(a[r]-a[l-1]-1)+1);};
	auto unban=[&](int l,int r,int m){return abs(a[l-1]+a[r]-a[m]*2);};
	vector<vector<vector<pll> > >ve(n+1,vector<vector<pll> >(n+1));
	vector<ll>ans(n+1);
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=n;l++)
		{
			int r=l+len-1;
			for(int m=l;m<r;m++)
			{
				ll ml=1e18,mr=ml;
				if(m==l)ml=0;
				if(m==r-1)mr=0;
				auto b=unban(l,r,m);
				int pl=lower_bound(ve[l][m].begin(),ve[l][m].end(),(pll){b+1,0})-ve[l][m].begin()-1;
				int pr=lower_bound(ve[m+1][r].begin(),ve[m+1][r].end(),(pll){b+1,0})-ve[m+1][r].begin()-1;
				if(pl>=0)cmin(ml,ve[l][m][pl].second);
				if(pr>=0)cmin(mr,ve[m+1][r][pr].second);
				ans[m]=ml+mr+cost(l,r,m);
				if(ans[m]<1e18)ve[l][r].emplace_back(b,ans[m]);
			}
			sort(ve[l][r].begin(),ve[l][r].end());
			for(int i=1;i<ve[l][r].size();i++)cmin(ve[l][r][i].second,ve[l][r][i-1].second);
		}
	}
	for(int i=1;i<n;i++)
	{
		if(ans[i]<1e18)cout<<ans[i]<<' ';
		else cout<<-1<<' ';
	}
	cout<<'\n';

}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
} 
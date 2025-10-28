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
int mod=998244353;
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
    int n;
	cin>>n>>mod;
	vii F(n+1,vi(n+1));
	vi jc(n+1);jc[0]=1;
	vi po(n+1);
	po[0]=1;
	for(int i=1;i<=n;i++)MOD(po[i]=po[i-1]<<1);
	for(int i=1;i<=n;i++)jc[i]=mul(jc[i-1],i);
	vii c(n+1,vi(n+1));
	for(int i=0;i<=n;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++)MOD(c[i][j]=c[i-1][j-1]+c[i-1][j]);
	}
	for(int i=1;i<=n;i++)
	{
		F[i][i]=po[i];
		for(int j=1;j<=i;j++)
		{
			for(int k=0;k<i;k++)
			{
				MOD(F[i][j]+=mul(F[k][j-(i-k)]));
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
} 
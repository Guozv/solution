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
    int m,n;
	cin>>m>>n;
	vi a(n+1);
	vi pos(m+1);
	for(int i=1;i<=n;i++)cin>>a[i],pos[a[i]]=i;
	vii F(n+2,vi(n+2)),g=F;
	if(pos[0])F[pos[0]][pos[0]+1]=1;
	else for(int i=1;i<=n+1;i++)F[i][i]=1;
	
	for(int x=1;x<m;x++)
	{
		F.swap(g);
		F.assign(n+2,vi(n+2));
		if(pos[x])
		{
			for(int i=1;i<=n+1;i++)
				for(int j=i;j<=n+1;j++)
					MOD(F[min(i,pos[x])][max(j,pos[x]+1)]+=g[i][j]);
		}
		else
		{
			for(int i=1;i<=n+1;i++)
			{
				int sum=0;
				for(int j=i;j<=n+1;j++)
				{
					MOD(sum+=g[i][j]);
					MOD(F[i][j]+=sum);
				}
			}
			for(int j=n+1;j;j--)
			{
				int sum=0;
				for(int i=j;i;i--)
				{
					MOD(sum+=g[i][j]);
					MOD(F[i][j]+=sum);
				}
			}
		}
	}
	cout<<F[1][n+1]<<endl;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
} 
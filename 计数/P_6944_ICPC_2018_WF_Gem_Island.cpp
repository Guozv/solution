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
const int MAXN=500+10;
LD C[MAXN][MAXN],F[MAXN][MAXN],g[MAXN][MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,d,r;cin>>n>>d>>r;
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	F[0][n]=1,g[0][n]=r;
	for(int s=0;s<d;s++)
	{
		for(int i=1;i<=n;i++)
			for(int x=1;s+x<=d&&x<=i;x++)
			{
				F[s+x][x]+=F[s][i]*C[i][x];
				g[s+x][x]+=(g[s][i]+min(r,x)*F[s][i])*C[i][x];
			}
	}
	LD s1=0,s2=0;
	for(int i=1;i<=n;i++)s1+=F[d][i],s2+=g[d][i];
	//cerr<<s1<<" "<<s2<<endl;
	cout<<s2/s1<<endl;
	return 0;
} 
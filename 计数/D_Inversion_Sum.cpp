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
int inv2=(mod+1)>>1;
inline void solve()
{
    int n,q;cin>>n>>q;
	vi a(n+1);
	vii F(n+1,vi(n+1));
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			F[i][j]=a[i]>a[j];
	int p=ksm(2,q);
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		if(x>y)swap(x,y);
		for(int i=1;i<=n;i++)if(i!=x&&i!=y)
		{
			F[x][i]=F[y][i]=mul(F[x][i]+F[y][i],inv2);
			F[i][x]=F[i][y]=mul(F[i][x]+F[i][y],inv2);
		}
		F[x][y]=F[y][x]=mul(F[x][y]+F[y][x],inv2);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			MOD(ans+=F[i][j]);
	cout<<mul(ans,p)<<endl;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
} 
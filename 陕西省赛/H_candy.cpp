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
vi r;
const int g=3,invg=332748118;
ll inv;
int lim;
inline void prework(int n)
{
	int cnt=-1;
	lim=1;
	while(lim<n)lim<<=1,cnt++;
	r.resize(lim);
	for(int i=0;i<lim;i++)r[i]=(r[i>>1]>>1)|((1&i)<<cnt);
}
inline void ntt(vi& a,int op)
{
	for(int i=0;i<lim;i++)if(i<r[i])swap(a[i],a[r[i]]);
	for(int m=1;m<lim;m<<=1)
	{
		ll Wn=ksm(op?g:invg,(mod-1)/(2*m));
		for(int i=0;i<lim;i+=m*2)
		{
			ll w=1;
			for(int j=0;j<m;j++,w=w*Wn%mod)
			{
				int x=a[i+j],y=w*a[i+j+m]%mod;
				a[i+j]=(x+y)%mod,a[i+j+m]=(x+mod-y)%mod;
			}
		}
	}
	inv=ksm(lim);
	if(op==0)for(int i=0;i<lim;i++)a[i]=inv*a[i]%mod;
}
inline void solve()
{
    int n;cin>>n;
    string s;cin>>s;
    s=' '+s;
    vii F(n+1,vi(n+1));
	F[0][0]=1;
	int ans=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=n;j++)
		{
			MOD(F[i+1][j]+=F[i][j]);
			if(s[i+1]=='1')MOD(F[i+1][max(0,j-1)]+=F[i][j]);
			else if(j<n)MOD(F[i+1][j+1]+=F[i][j]);
		}
		if(s[i+1]=='1')MOD(ans+=ksm(2,n-i-1)*F[i][0]%mod);
	}
	cout<<ksm(ksm(2,n))*ans%mod<<endl;
}
int main()
{
	//cerr<<748683265ll*4%mod<<endl;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
} 
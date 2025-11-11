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
const int MAXN=1.5e7+10;
int fc[MAXN*2],ifc[MAXN*2];
bitset<MAXN>is;
int p[MAXN/12],cnt;
inline int C(int n,int k)
{
	if(n<0||k<0||n<k)return 0;
	return mul(fc[n],ifc[k],ifc[n-k]);
}
int z[MAXN];
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,d,r;
	cin>>n>>d>>r;
	fc[0]=1;
	for(int i=1;i<=n+d;i++)fc[i]=mul(fc[i-1],i);
	ifc[n+d]=ksm(fc[n+d]);
	for(int i=n+d;i;i--)ifc[i-1]=mul(ifc[i],i);
	for(int i=2;i<=d;i++)
	{
		if(!is[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=d;j++)
		{
			is[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=d;i++)z[i]=C(d-i+n-1,n-1);
	for(int i=1;i<=cnt;i++)
		for(int j=d/p[i];j;j--)
			MOD(z[j]+=z[j*p[i]]);
	int ans=0;
	int t=min(d,r);
	for(int i=1;i<=n;i++)
	{
		int sk=0;
		if(t&1)sk=mod-mul(i,C(i-2,t-1));
		else sk=mul(i,C(i-2,t-1));
		if(d>r)
		{
			int s=d&1?mod-C(i-1,d):C(i-1,d);
			if(r&1)MOD(s+=C(i-1,r));
			else MOD(s+=mod-C(i-1,r));
			MOD(sk+=mul(s,r));
		}if(i&1)sk=mod-sk;
		if(i==1)sk=1;
		
		MOD(ans+=mul(C(n,i),z[i],sk));
	}
	//cerr<<ans<<endl;
	
	ans=ksm(C(n+d-1,d))*ans%mod;
	MOD(ans+=r);
	cout<<ans;
	return 0;
} 
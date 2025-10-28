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
const int MAXN=500+10;
int inv[MAXN];
struct poly:vi
{
	int n;
	int l,r;
	poly():vi(){}
	poly(int _n,int _l=0,int _r=0,int c=0):n(_n),l(_l),r(_r),vi(_n+1){front()=c;}
	inline poly& operator+=(const poly&b)
	{
		cmax(n,b.n);
		while(size()<=n)push_back(0);
		l|=b.l,r|=b.r;
		for(int i=0;i<=b.n;i++)MOD((*this)[i]+=b[i]);
		return *this;
	}
	inline int get(int N)
	{
		int x=1;
		int ans=0;
		for(int i=0;i<=n;i++)
		{
			MOD(ans+=mul(x,(*this)[i]));
			x=mul(x,N-i);
		}
		return ans;
	}
	inline poly integral()const
	{
		poly ans(n+1,l,r,0);
		//cerr<<n<<' '<<size()<<endl;
		for(int i=0;i<=n;i++)ans[i+1]=mul((*this)[i],inv[i+1]);
		MOD(ans[0]=mod-ans.get(l));
		return ans;
	}
	inline int sum()
	{
		return integral().get(r+1);
	}
};
inline void solve()
{
    int n;
	cin>>n;
	for(int i=1;i<=n;i++)inv[i]=ksm(i);
	vector<poly>f={poly(1,0,0,1)},g;

	for(int i=1;i<=n;i++)
	{
		auto add=[&](const poly& ve){if(ve.l<=ve.r)f.emplace_back(ve);};
		
		int l,r;cin>>l>>r;
		g.swap(f);
		f={poly(1,0,0,1)};
		int j=1;
		int C=1;
		//cerr<<i<<"!\n";
		for(j=1;j<g.size()&&g[j].r<l;j++)MOD(C+=g[j].sum()),f.emplace_back(g[j]);
		if(j>=g.size())
		{
			add(poly(1,f.back().r+1,l-1,0));
			add(poly(1,l,r,C));
			continue;
		}
		if(g[j].l<l)
		{
			//cerr<<"!\n";
			f.emplace_back(g[j]);
			f.back().r=l-1;
			//cerr<<l<<endl;
			MOD(C+=f.back().sum());
			g[j].l=l;
		}
		//cerr<<g[j].r<<endl;
		while(j<g.size()&&g[j].r<=r)f.emplace_back(g[j]),f.back()+=g[j].integral(),MOD(f.back()[0]+=C),MOD(C+=g[j].sum()),j++;
		//cerr<<f.back().r<<endl;
		//cerr<<i<<" "<<f.back().r<<endl;
		if(j>=g.size())
		{
		//	cerr<<f.back().r<<' '<<r<<endl;
			add(poly(1,f.back().r+1,r,C));
			continue;
		}
		if(g[j].l<=r)
		{
			f.push_back(g[j]);
			f.back().r=r;
			f.back()+=f.back().integral();
			MOD(f.back()[0]+=C);
			g[j].l=r+1;
		}
		while(j<g.size())f.emplace_back(g[j++]);
	}
	int ans=0;
	//cerr<<f[3].l<<' '<<f[3].r<<endl;
	//cerr<<f[3][0]<<" "<<f[3][1]<<endl;
	//cerr<<f[3].sum()<<endl;
	for(int i=1;i<f.size();i++)MOD(ans+=f[i].sum());
	cout<<ans;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
} 
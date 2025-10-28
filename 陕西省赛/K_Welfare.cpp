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
    ll n,m,x,y;
    cin>>n>>m>>x>>y;
   
    if(!n)
    {
        if(!m)
        {
            cout<<0<<endl;
            return;
        }
        if(x>y)cout<<x<<'\n';
        else cout<<1ll*m*y<<'\n';
        return;
    } 
    if(!y)
    {
        cout<<x<<endl;
        return;
    }
    if(x<=y)
    {
        cout<<1ll*(n+m)*y<<endl;
        return;
    }
    if(!m)
    {
        cout<<max<ll>(x,1ll*(n-1)*y+x)<<'\n';
        return;
    }
    int cnt=(x-1)/y;
    ll ans=1ll*(n)*y+x;
    if(cnt<=n)cmax(ans,x*(cnt!=0)+1ll*(n+m-cnt)*y);
    cout<<ans<<endl;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	cin>>T;
	while(T--)solve();
	return 0;
} 
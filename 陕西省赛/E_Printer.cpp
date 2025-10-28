#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
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
int cnt[30];

inline void solve()
{
    int n,m,t;cin>>n>>m>>t;
    vii w(m,vi(m));
    string a;cin>>a;
    a='a'+a;
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            cin>>w[i][j];
    vii F(1<<n,vi(n+1,1e9));
    F[0][0]=0;
 //   cerr<<F.size()<<endl;
    for(int s=0;s<(1<<n);s++)
        for(int x=0;x<=n;x++)
        if(F[s][x]!=1e9)
        {
           
            for(int i=0;i<n;i++)cnt[i+1]=cnt[i]+(s>>i&1);
            for(int i=1;i<=n;i++)if((~s)>>(i-1)&1)
            {
                int l=min(i,x),r=max(i,x);
                int v1=(cnt[r]-cnt[l])*t;
                int v2=w[a[x]-'a'][a[i]-'a'];
               // cerr<<v1<<' '<<v2<<endl;
                cmin(F[s|(1<<(i-1))][i],F[s][x]+v1+v2+t);
            }
        }
    int ans=1e9;
    for(int i=0;i<=n;i++)
        cmin(ans,F[(1<<n)-1][i]);
    cout<<ans<<endl;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
	//cin>>T;
	while(T--)solve();
	return 0;
} 
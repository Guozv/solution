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
inline ll ksm(ll a,ll p=mod-2)
{
    ll ans=1;
    for(;p;p>>=1,a=a*a%mod)if(p&1)ans=ans*a%mod;
    return ans;
}
const int MAXN=2e5+10;
int jc[MAXN];
inline void solve()
{
    int n,k;
    cin>>n>>k;
    vi b(n+1);
    for(int i=1;i<=n;i++)cin>>b[i];
    vi jc(n+1);
    jc[0]=1;
    for(int i=1;i<=n;i++)jc[i]=1ll*jc[i-1]*i%mod;
    vector<ll> a(n+2);
    for(int i=n;i;i--)a[i]=b[i]+(i+k>n?0:a[i+k]);
    for(int i=1;i<=n;i++)a[i]=a[i+1]-a[i];
    vi F(n+2);
    iota(F.begin(),F.end(),0);
    function<int(int)>getf=[&](int x)->int {return F[x]==x?x:F[x]=getf(F[x]);};
    
    for(int i=k;i+k<=n;i++)F[getf(i)]=getf(i+k);
    vector<vector<ll> > ve(n+2);
    for(int i=1;i<=n;i++)ve[getf(i)].emplace_back(a[i]);
    ll ans=1;
   // for(int i=1;i<=n;i++)cerr<<a[i]<<" ";cerr<<endl;
    for(int i=1;i<=n;i++)if(getf(i)==i)
    {
        auto&c=ve[i];
        sort(c.begin(),c.end());
        int i=0,j=0;
       // cerr<<c.size()<<endl;
        while(i<c.size())
        {
            j=i;
            while (j<c.size()&&c[i]==c[j])
            {
                j++;
            }
            ans=ans*ksm(jc[j-i])%mod;
            i=j;
        }
        ans=ans*jc[c.size()]%mod;
    }
    cout<<ans<<endl;
}
int main()
{
    
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
   // cin>>T;
    while(T--)solve();
	return 0;
} 
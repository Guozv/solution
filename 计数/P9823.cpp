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
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,k;
    cin>>n>>k;
    vi sum(n+1);
    vi inv(n+1);
    inv[1]=1;
    for(int i=2;i<=n;i++)inv[i]=mul(inv[mod%i],mod-mod/i);
    sum[0]=1;
    int jc=1,f;
    for(int i=1;i<=n;i++)
    {
        f=sum[i-1];
        if(i-k-1>=0)MOD(f+=mod-sum[i-k-1]);
        f=mul(f,inv[i]);
        MOD(sum[i]=sum[i-1]+f);
        jc=mul(jc,i);
    }
    cout<<mul(f,jc);
	return 0;
} 
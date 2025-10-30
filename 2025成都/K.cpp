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
struct xds
{
    xds*ls,*rs;
    int l,r;
    int mmax,add;
    xds(int L,int R):l(L),r(R)
    {
        add=0;mmax=0;
        if(L==R)return ;
        int mid=(L+R)>>1;
        ls=new xds(L,mid),rs=new xds(mid+1,R);
    }
    ~xds(){if(l==r)return;delete ls,rs;}
    inline void ADD(int k){add+=k,mmax+=k;}
    inline void push_down()
    {
        if(add)ls->ADD(add),rs->ADD(add),add=0;
    }
    inline void push_up(){mmax=max(ls->mmax,rs->mmax);}
    void update(int ql,int qr,int k)
    {
        if(ql>qr)return;
        if(ql<=l&&r<=qr)return ADD(k);
        push_down();
        int mid=(l+r)>>1;
        if(ql<=mid)ls->update(ql,qr,k);
        if(qr> mid)rs->update(ql,qr,k);
        push_up();
    }
};
inline void solve()
{
    int n,L,k;cin>>n>>L>>k;
    vi l(n+1);
    for(int i=1;i<=n;i++)cin>>l[i];
    sort(l.begin()+1,l.end());
    int N=n*2+L+L;
    vi d(N+2);
    vi ve(N+1,n+1);
    for(int i=1;i<=n;i++)cmin(ve[l[i]],i),d[l[i]]++,d[l[i]+L]--;
    for(int i=1;i<=N;i++)d[i]+=d[i-1];
    int pos=n+1;
    xds t(1,n);
    int cnt=0;
    for(int i=0;i<=n*2+L;i++)cnt+=d[i]==k;
    int p=n;
    int ans=0;
  //  cerr<<cnt<<endl;
    for(int i=n*2;~i;i--)
    {
        cmin(pos,ve[i]);
        while(p&&l[p]>i+L-1)p--;
        if(pos==n+1)continue;
        cmax(ans,cnt+t.mmax);
        if(!i)continue;
        int x=d[i-1]==k-1;
        x-=d[i-1]==k;
        x-=d[i+L-1]==k-1;
        x+=d[i+L-1]==k;
        t.update(p+1,n,x);
        x=0;
        x+=d[i-1]==k-1;
        x-=d[i-1]==k;
        x-=d[i+L-1]==k;
        x+=d[i+L-1]==k+1;
        t.update(pos,p,x);
  //      cerr<<pos<<' '<<p<<' '<<t.mmax<<endl;
        
    }
    xds t2(1,n);
    ve.assign(N+1,-1);
    for(int i=1;i<=n;i++)cmax(ve[l[i]+L-1],i);
    pos=-1;
    p=0;
    for(int i=L-1;i<=2*n+L+L;i++)
    {
     //   cerr<<"!\n";
        cmax(pos,ve[i]);
        while(p<=n&&l[p]+L-1<i-L+1)p++;
        if(pos<=0)continue;
        
       // cerr<<i<<' '<<t2.mmax<<' '<<p<<' '<<pos<<endl;
        cmax(ans,cnt+t2.mmax);
        int x=d[i+1]==k-1;
        x-=d[i+1]==k;
        x+=d[i-L+1]==k,x-=d[i-L+1]==k-1;
        t2.update(1,p-1,x);
      //  cerr<<1<<' '<<p-1<<endl;
        x=0;
        x-=d[i+1]==k;
        x+=d[i+1]==k-1;
        x+=d[i-L+1]==k+1;
        x-=d[i-L+1]==k;  
        t2.update(p,pos,x);
    }
    cout<<ans<<endl;
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T;cin>>T;
    while(T--)solve();
	return 0;
} 
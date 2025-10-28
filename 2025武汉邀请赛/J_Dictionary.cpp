#include<bits/stdc++.h>
using namespace std;
# pragma GCC ("Ofast")
typedef long long ll;
using i64=long long ;
const int MAXN=4e5+10;
int cnt[MAXN],X[MAXN],Y[MAXN],sa[MAXN],rk[MAXN],hi[MAXN];
int *x=X,*y=Y;
string s;
inline void get_sa(int n,int m)
{   
    for(int i=1;i<=m;i++)cnt[i]=0;
	for(int i=1;i<=n;i++)cnt[x[i]=s[i-1]]++;
    for(int i=n+1;i<=n*2;i++)x[i]=y[i]=0;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[x[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
		x[sa[1]]=1,p=1;
		for(int i=2;i<=n;i++)x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p==n)break;
		m=p;
	}
 //   cerr<<s<<endl;
    for(int i=1;i<=n;i++)rk[sa[i]]=i;
   //  for(int i=1;i<=n;i++)cerr<<rk[i]<<' ';cerr<<endl;
    for(int i=1,k=0;i<=n;i++)
    {
        if(rk[i]==1)continue;
        if(k)k--;
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k-1]==s[j+k-1])k++;
        hi[rk[i]]=k;
    }
}

const int K=18;
int F[K+1][MAXN];
inline int ask(int l,int r)
{
    if(l>r)return s.size()-sa[r]+1;
    int k=__lg(r-l+1);
    return min(F[k][l],F[k][r-(1<<k)+1]);
}
struct node
{
    mutable ll w;
    int l,r;
    node(int L,int R=-1,ll W=0):l(L),r(R),w(W){}
    inline bool operator<(const node& b)const
    {
        return l<b.l;
    }
};
typedef long long ll;
struct C:set<node>
{
    auto split(int pos)
    {
        auto ii=lower_bound(node(pos));
        if(ii!=end()&&ii->l==pos)return ii;ii--;
        node w=*ii;
        erase(ii);
        insert(node(w.l,pos-1,w.w));
        return insert(node(pos,w.r,w.w)).first;
    }
    inline ll assign(int l,int r,ll a)
    {
        auto endd=split(r+1),ii=split(l);
        ll ans=0;
        while(ii!=endd)
        {
            ans+=1ll*(ii->r-ii->l+1)*ii->w;
            erase(ii++);
        }
        insert(node(l,r,a));
        return ans;
    }
    inline int cal(int l,ll d)
    {
        auto endd=split(l+1),ii=split(l);
        ll ans=max(0ll,ii->w-d);
        ii->w=min(ii->w,d);
        return ans;
    }
};
inline void solve()
{
    cin>>s;
    int n=s.size();
    get_sa(s.size(),'z');
    for(int i=1;i<=n;i++)F[0][i]=hi[i];
    for(int i=1;i<=K;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            F[i][j]=min(F[i-1][j],F[i-1][j+(1<<(i-1))]);
    int T;cin>>T;
    ll ans=0;
   // for(int i=1;i<=n;i++)cerr<<hi[i]<<" ";cerr<<endl;
    C ss;
    for(int i=1;i<=n;i++)ss.insert(node(i,i,n-sa[i]+1-hi[i]));
    while(T--)
    {
        int l,r;cin>>l>>r;
        int x=rk[l];
      //  cerr<<x<<endl;
        int ansr=x,L=x+1,R=n;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(ask(x+1,mid)>=r-l+1)ansr=mid,L=mid+1;
            else R=mid-1;
        }
        int ansl=x;L=1,R=x-1;
        while(L<=R)
        {
            int mid=(L+R)>>1;
            if(ask(mid+1,x)>=r-l+1)ansl=mid,R=mid-1;
            else L=mid+1;
        }
        int d=max(0,r-l+1-1-hi[ansl]);
        if(ansl+1<=ansr)ans+=ss.assign(ansl+1,ansr,0);
       
        ans+=ss.cal(ansl,d);
        cout<<ans<<' ';
    }
    cout<<'\n';
}
int main()
{
    int T;cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
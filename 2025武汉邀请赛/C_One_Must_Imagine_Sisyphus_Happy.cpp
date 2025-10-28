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
const int MAXN=2e5+10;
inline void solve()
{
    int n,m;cin>>n>>m;
    vi a(n+1);
    for(int i=1;i<=n;i++)cin>>a[i];
    vi g1(m+1),g2(m+1),g3(m+1);
    int T=2*n-1;
    for(int i=1;i<n;i++)
    {
        int k=a[i]/T;//游戏进行的轮数
        if(k>=m)continue;//只能第一轮被割
        a[i]%=T;
        if(a[i]>=(n-i)*2)g1[k+1]++;//一直在 1->n 的时候被割
        else if(a[i]>=(i-1)*2+1)g2[k+1]++;//一直在 n->1 的时候被割
        else  g3[k+1]++;
    }
    //注意特殊处理 a[n]
    if(a[n]/T<m)g1[a[n]/T+1]++;
    vector<ll> ans(m+1);
    ans[1]=n;
    for(int i=1;i<=m;i++)
    {
        for(int j=i+1;j<=m;j+=i)ans[j]+=g1[i];
        for(int j=i;j<=m;j+=i)ans[j]+=g2[i];
        for(int j=i,u=1;j<=m;j+=i-(u^=1))ans[j]+=g3[i];
    }
    for(int i=1;i<=m;i++)cout<<ans[i]<<' ';cout<<'\n';
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int T=1;
    cin>>T;
    while(T--)solve();
	return 0;
} 
/*
一个并不难的题，首先这个题一定是有周期的，一个来回 2n-1 为一个周期

对于一块草，我们分析它在什么时候会被砍。

首先第一次到 n 的时候，所有的草都会被砍

然后回来的时候，如果 a_i%T 大于 (n-i)*2 那回来的时候不会被割,也就是只会在去的时候被割

如果 a_i%T 大于等于 (i-1)*2+1 那说明再一次去的时候也不会被割，只会在回来的时候被割

否则去跟回都会被割。

然后注意特殊处理一下 a[n] 

枚举这个间隔的周期数统计答案，复杂度调和级数

*/
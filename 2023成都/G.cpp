#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
typedef long double LD;
#define double long double
const double eps=1e-12;
inline int sign(double x){return fabs(x)<=eps?0:(x>0?1:-1);}
struct Vector
{
    double x,y;
    Vector(double X,double Y):x(X),y(Y){}
    Vector(){}
    inline Vector operator+(const Vector& b)const{return {x+b.x,y+b.y};}
    inline Vector operator-(const Vector& b)const{return {x-b.x,y-b.y};}
    inline double operator *(const Vector& b)const{return x*b.x+y*b.y;}
    inline double operator %(const Vector& b)const{return x*b.y-y*b.x;}
    inline double len()const{return sqrt((*this)*(*this));}
    inline double operator &(const Vector& b)const{return ((*this)-b).len();}
    inline Vector operator *(const double& b)const{return {x*b,y*b};}
    inline Vector operator /(const double& b)const{return {x/b,y/b};}
    inline bool operator<(const Vector&b)const{return x<b.x||fabs(x-b.x)<eps&&y<b.y;}
    inline double angle()const{return atan2(y,x);}
};
typedef Vector point;
inline istream& operator>>(istream&in,point& a)
{
    return in>>a.x>>a.y;
}
inline ostream& operator<<(ostream&in,const point& a)
{
    return in<<a.x<<' '<<a.y;
}
inline ll dis(point a,point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
struct line
{
    point a;Vector v;
    double angle;
    line(point x,point y):a(x),v(y-x),angle(v.angle()){}
    line(){}
};
inline point getpoint(line l1,line l2)
{
    Vector u(l1.a-l2.a);
    return l1.a+l1.v*(l2.v%u)/(l1.v%l2.v);
}

const int MAXN=2000+10;
point a[MAXN];
const LD pi=acosl(-1);
line q[MAXN*MAXN+10];
point p[MAXN*MAXN];
inline bool onleft(line a,point b){return a.v%(b-a.a)>0;}
inline LD cal(vector<point>ve,point U)
{
    
    sort(ve.begin(),ve.end());
    //cerr<<ve[0]<<endl<<ve[1]<<endl<<ve[2]<<endl;
    auto cal=[&](point a,point b,point c)->LD
    {
        LD dx=b.x-a.x;
        if(sign(dx)==0)return 0.0;
        point p1=b-a,p2=(c-a)*(b.x-a.x)/(c.x-a.x);
        //cerr<<"! "<<(p1-p2).len()<<endl;
        return (p1-p2).len()*abs(dx)*(dx*dx*0.25+2*dx*(a.x-U.x)/3+(a.x-U.x)*(a.x-U.x)*0.5);
    };
    LD ans=cal(ve[0],ve[1],ve[2])+cal(ve[2],ve[1],ve[0]);
    //cerr<<cal(ve[0],ve[1],ve[2])<<endl;
    //cerr<<cal(ve[2],ve[1],ve[0])<<endl;
    //cerr<<ans<<endl;
    swap(U.x,U.y);
    for(auto&p:ve)swap(p.x,p.y);
    sort(ve.begin(),ve.end());
    //cerr<<cal(ve[2],ve[1],ve[0])<<endl;
    ans+=cal(ve[0],ve[1],ve[2])+cal(ve[2],ve[1],ve[0]);
    //cerr<<ans<<endl;
    return ans;
}
inline LD cal(vector<line>a,point U)
{
    sort(a.begin(),a.end(),[&](line a,line b){return a.angle<b.angle||!sign(a.angle-b.angle)&&!onleft(a,b.a);});
	int h=1,t=0;q[++t]=a[0];
	for(int i=1;i<a.size();i++)
	{
        if(!sign(a[i].angle-a[i-1].angle))continue;
		while(h<t&&!onleft(a[i],p[t-1]))t--;
		while(h<t&&!onleft(a[i],p[h]))h++;
		q[++t]=a[i];
		if(h<t&&!sign(q[t].v%q[t-1].v))
		{
			t--;
			if(onleft(q[t],a[i].a))q[t]=a[i];
		}
		if(h<t)p[t-1]=getpoint(q[t-1],q[t]);
	}
	while(h<t&&!onleft(q[h],p[t-1]))t--;
    if(t-h<=1)return 0;
    //cerr<<"!" <<h<<" "<<t<<endl;
   // cerr<<"U: "<<U<<endl;
    p[t]=getpoint(q[t],q[h]);
   // for(int i=h;i<=t;i++)cerr<<p[i]<<endl;
    q[t+1]=q[h];
    LD ans=0;
    for(int i=h+1;i<t;i++)
    {
        ans+=cal({p[h],p[i],p[i+1]},U);
    }
   // cerr<<ans<<endl;
    return ans;
}
signed main() {
    cin.tie(0), ios::sync_with_stdio(0);
    cout<<fixed<<setprecision(20);
    int x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    LD ans=0;
    for(int i=1;i<=n;i++)
    {
        auto U=a[i];
        vector<line>ve;
        // ve.emplace_back(point(x1,y1),point(x1,y2));
        // ve.emplace_back(point(x1,y2),point(x2,y2));
        // ve.emplace_back(point(x2,y2),point(x2,y1));
        // ve.emplace_back(point(x2,y1),point(x1,y1));
        ve.emplace_back(point(x1,y2),point(x1,y1));
        ve.emplace_back(point(x2,y2),point(x1,y2));
        ve.emplace_back(point(x2,y1),point(x2,y2));
        ve.emplace_back(point(x1,y1),point(x2,y1));
        for(int j=1;j<=n;j++)if(i!=j)
        {
            Vector p=a[j]-a[i];
            point mid=(a[i]+a[j])/2;
            
            ve.emplace_back(mid,mid+Vector(p.y,-p.x));
        }
       
        ans+=cal(ve,a[i]);
        ve.clear();
        ve.emplace_back(point(x1,y2),point(x1,y1));
        ve.emplace_back(point(x2,y2),point(x1,y2));
        ve.emplace_back(point(x2,y1),point(x2,y2));
        ve.emplace_back(point(x1,y1),point(x2,y1));
        for(int j=1;j<=n;j++)if(i!=j)
        {
            Vector p=a[j]-a[i];
            point mid=(a[i]+a[j])/2;
            ve.emplace_back(mid,mid+Vector(-p.y,p.x));
        }       
        ans-=cal(ve,a[i]);
    }
    cout<<ans*pi/(x2-x1)/(y2-y1);
    return 0;
}
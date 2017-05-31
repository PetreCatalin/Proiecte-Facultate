#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct punct{
    int x,y;
}a,b,c,d,m;

int det(punct a,punct b,punct c)
{
    int d;
    d=b.x*c.y+a.x*b.y+a.y*c.x-b.x*a.y-c.x*b.y-c.y*a.x;
    return d;
}

void convex()
{
    int s1,s2,s3;
    s1=det(a,b,c);
    s2=det(b,c,d);
    s3=det(c,d,a);
    if (s1>0 &&s2>0 &&s3>0) cout<<"Patrulaterul este convex\n";
    else
    if (s1<0 &&s2<0 &&s3<0) cout<<"Patrulaterul este convex\n";
    else
    cout<<"Patrulaterul nu e convex\n";
}

double arie(punct a,punct b,punct c)
{
    double ar=(double) abs(det(a,b,c))/2;
    return ar;
}

int main()
{
    cout<<"Introduceti cele 4 puncte ale patrulaterului\n";
    cin>>a.x>>a.y>>b.x>>b.y>>c.x>>c.y>>d.x>>d.y;
    convex();
    cout<<"Introduceti punctul M\n";
    cin>>m.x>>m.y;
    double s,h1,h2,h3;
    int ok=0;
    s=arie(a,b,c);h1=arie(a,b,m);h2=arie(b,c,m);h3=arie(c,a,m);
    if (s==h1+h2+h3) {ok=1;cout<<"Punctul M apartine acoperirii convexe\n";}
    if (ok==0) {
        s=arie(b,c,d);h1=arie(b,c,m);h2=arie(c,d,m);h3=arie(b,d,m);
        if (s==h1+h2+h3) {ok=1;cout<<"Punctul M apartine acoperirii convexe\n";}
    }
    if (ok==0) {
        s=arie(a,c,d);h1=arie(a,c,m);h2=arie(a,d,m);h3=arie(c,d,m);
        if (s==h1+h2+h3) {ok=1;cout<<"Punctul M apartine acoperirii convexe\n";}
    }
    if (ok==0) {
        s=arie(a,b,d);h1=arie(a,b,m);h2=arie(b,d,m);h3=arie(a,d,m);
        if (s==h1+h2+h3) {ok=1;cout<<"Punctul M apartine acoperirii convexe\n";}
    }
    if (ok==0) cout<<"Punctul M nu apartine acoperirii convexe\n";

}

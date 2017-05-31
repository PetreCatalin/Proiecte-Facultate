#include <bits/stdc++.h>

using namespace std;

struct punct{
    int x,y;
    char p;
}A,B,C,D;

punct aux;
double int1,int2,mab,mcd;
double s1x,s1y,s2x,s2y,s,t;
int x1,x2,i,j;

int det(punct A,punct B,punct C)
 {
 return A.x*B.y+ B.x*C.y+C.x*A.y-B.x*A.y-C.x*B.y-C.y*A.x;
 }

int main()
{
    A.p='A';B.p='B';C.p='C';D.p='D';
    cout<<"Introduceti cele 4 puncte\n";
    cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y>>D.x>>D.y;
    x1=det(A,B,C);
    x2=det(B,C,D);
    if (x1==0 &&x2==0) {
        cout<<"Punctele sunt coliniare\n";
        punct v[5];
            v[0].x=A.x;v[0].y=A.y;v[0].p=A.p;
            v[1].x=B.x;v[1].y=B.y;v[1].p=B.p;
            v[2].x=C.x;v[2].y=C.y;v[2].p=C.p;
            v[3].x=D.x;v[3].y=D.y;v[3].p=D.p;

    if (A.x==B.x &&A.x==C.x &&A.x==D.x) { //dreapta verticala
        for (i=0;i<=2;++i)
            for (j=i+1;j<=3;++j)
                if (v[i].y>v[j].y) {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }

    if  ((v[1].p=='A' &&v[0].p=='B') || (v[1].p=='B' &&v[0].p=='A') || (v[1].p=='C' &&v[0].p=='D') || (v[1].p=='D' &&v[0].p=='C'))
        cout<<"Segmentele nu se intersecteaza\n";
    else {
        cout<<"Segmentul de intersectie este:";
        cout<<v[1].p<<v[2].p<<'\n';
    }
    }

    else { //nu e dreapta verticala
        for (i=0;i<=2;++i)
            for (j=i+1;j<=3;++j)
                if (v[i].x>v[j].x) {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }

    if  ((v[1].p=='A' &&v[0].p=='B') || (v[1].p=='B' &&v[0].p=='A') || (v[1].p=='C' &&v[0].p=='D') || (v[1].p=='D' &&v[0].p=='C'))
        cout<<"Segmentele nu se intersecteaza\n";
    else {
        cout<<"Segmentul de intersectie este:";
        cout<<v[1].p<<v[2].p<<'\n';
    }

    }
    }

    else {
        cout<<"Punctele nu sunt coliniare\n";
        s1x=B.x-A.x; s1y=B.y-A.y;
        s2x=D.x-C.x; s2y=D.y-C.y;
        s=(-s1y*(A.x-C.x)+s1x*(A.y-C.y))/(-s2x*s1y+s1x*s2y);
        t=(s2x*(A.y-C.y)-s2y*(A.x-C.x))/(-s2x*s1y+s1x*s2y);
        if (s>=0 &&s<=1&&t>=0 &&t<=1) {
            cout<<"Punctul de intersectie este:";
            cout<<A.x+t*s1x<<' '<<A.y+t*s1y<<'\n';
        }
        else
            cout<<"Segmentele nu se intersecteaza\n";
    }
    return 0;
}

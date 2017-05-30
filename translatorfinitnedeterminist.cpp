#include <bits/stdc++.h>

using namespace std;

long n,x,i,nr,coada[100],t[100],y,lungime,j,inc,sf,sf1,stare,k,litera[100],v[100],ok;
char in,curent;
char out[10],cuvant[100],iesire[100][10];

struct tranzitie{
char input;
char output[10];
};

struct legatura{
    tranzitie v[10];
    int nr=0;
};

int main()
{
    cout<<"Numar de stari:"<<'\n';
    cin>>n;
    legatura a[n+2][n+2];

    cout<<"Starea initiala:"<<'\n';
    cin>>x;
    coada[1]=x;

    cout<<"Numarul de stari finale:"<<'\n';
    cin>>nr;
    int final[n+2];
    cout<<"Introduceti starile finale:"<<'\n';
    for (i=1;i<=nr;++i) {
        cin>>x;
        final[x]=1;
    }

    cout<<"Introduceti numarul de tranzitii:"<<'\n';
    cin>>nr;

    cout<<"Introduceti tranzitiile:"<<'\n';
    for (i=1;i<=nr;++i) {
        cin>>x>>y>>in>>out;
        a[x][y].nr++;
        a[x][y].v[a[x][y].nr].input=in;
        strcpy(a[x][y].v[a[x][y].nr].output,out);
    }

    cout<<"Introduceti cuvantul de translatat:"<<'\n';
    cin>>cuvant;
    lungime=strlen(cuvant);
    litera[1]=0;

    inc=1;sf=1;sf1=1;

     while (inc<=sf) {
        for (i=inc;i<=sf;++i) {
            stare = coada[i];
            if (litera[i]<lungime) {
            curent=cuvant[litera[i]];

            for (k=0;k<n;++k)
                for (nr=1;nr<=a[stare][k].nr;++nr) {
                if  (a[stare][k].v[nr].input==curent || a[stare][k].v[nr].input=='.') {
                        sf1++;
                        coada[sf1]=k;
                        t[sf1]=i;
                        strcpy(iesire[sf1],a[stare][k].v[nr].output);
                }
                if  (a[stare][k].v[nr].input==curent) litera[sf1]=litera[i]+1;
                if  (a[stare][k].v[nr].input=='.') litera[sf1]=litera[i];
                }
            }
        }
        inc=sf+1;
        sf=sf1;
    }

    ok=0;
    cout<<"Iesiri:"<<'\n';
    for (i=1;i<=sf;++i)
    if (final[coada[i]]==1 && litera[i]==lungime) {
        nr=1;ok=1;
        v[nr]=i;
        x = t[i];
        while (x!=0) {
            ++nr;
            v[nr]=x;
            x= t[x];
        }
        for (j=nr;j>=1;--j)
            if (strcmp(iesire[v[j]],".")!=0) cout<<iesire[v[j]];
        cout<<'\n';
    }

    if (ok==0) cout<<"Cuvantul nu e acceptat de translator"<<'\n';


  /*  for (i=1;i<=15;++i)
        cout<<coada[i]<<' ';
    cout<<'\n';
    for (i=1;i<=15;++i)
        cout<<t[i]<<' ';
    cout<<'\n';
    for (i=1;i<=15;++i)
        cout<<iesire[i]<<' ';
    cout<<'\n';
    for (i=1;i<=15;++i)
        cout<<litera[i]<<' ';
    cout<<'\n'; */

    return 0;
}

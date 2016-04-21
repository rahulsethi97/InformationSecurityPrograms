#include<bits/stdc++.h>
using namespace std;

int ext_euclidean_gcd(int x,int y)
{
    int a=x,b=y;
    int r,q,s1=1, s2=0 ,s3, t1=0 , t2=1,t3;         // s =1,0  // t= 0,1 a*s + b*t


    while(y!=0)
    {
        q=x/y;
        r = x - q*y;
        x=y;
        y=r;

        s3 = s1 - q*s2;
        s1=s2;
        s2=s3;

        t3 = t1 - q*t2;
        t1=t2;
        t2=t3;
    }

    cout<<"S: "<<s1<<" T: "<<t1<<"\n";
    return a*s1 + b*t1;
}

int main()
{


    int a,b;
    while(1)
    {
    cout<<"\nEnter the two numbers: ";
    cin>>a>>b;
    cout<<"\nGCD: "<<ext_euclidean_gcd(a,b);
    cout<<"\n";

    }

}

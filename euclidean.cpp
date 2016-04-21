#include<bits/stdc++.h>
using namespace std;

int euclidean_gcd(int x,int y)
{
    while(y!=0)
    {
        int temp=x;
        x=y;
        y=temp%y;
    }
    return x;
}

int main()
{


    int a,b;
    while(1)
    {
    cout<<"\nEnter the two numbers: ";
    cin>>a>>b;
    cout<<"\nGCD: "<<euclidean_gcd(a,b);
    cout<<"\n";

    }

}

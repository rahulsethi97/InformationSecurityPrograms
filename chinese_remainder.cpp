#include<bits/stdc++.h>
using namespace std;

int mult_inv(int x,int y)
{

    int r , q , s1=0 , s2=1 , s3;         // s =1,0  // t= 0,1 a*s + b*t
    int mod=y;

    while(x!=0)
    {
        q=y/x;
        r = y - q*x;
        y=x;
        x=r;

        s3 = s1 - q*s2;
        s1=s2;
        s2=s3;
    }
    int ans;
    if(s1<0)
        ans=(s1+mod)%mod;
    else
        ans=s1%mod;

    return ans;
}

int chinese_remainder(int arr[][2],int n)
{
    int M1[n],M1_inverse[n];
    int M=1;
    for(int i=0;i<n;i++)
        M*=arr[i][1];

    for(int i=0;i<n;i++)
      {
         M1[i]=M/arr[i][1];
         M1_inverse[i]=mult_inv(M1[i],arr[i][1]);
      }

    int ans=0;

    for(int i=0;i<n;i++)
    {
        ans+=arr[i][0]*M1_inverse[i]*M1[i];
    }

    return ans%M;
}

int main()
{


    int n;


    while(1)
    {
    cout<<"\nHow many equations you want: ";
    cin>>n;

    int arr[n][2];

     cout<<"\nEnter "<<n<<" pairs of a and m:\n";
     for(int i=0;i<n;i++)
     {
        cin>>arr[i][0];
        cin>>arr[i][1];
     }

     int x=chinese_remainder(arr,n);
     cout<<x<<"\n";
    }

}

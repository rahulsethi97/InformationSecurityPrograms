#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll arr[10000007];
ll p,q;

ll isPrime(ll x)
{
    for(ll i=2;i<=sqrt(x);i++)
    {
        if((x%i)==0)
            return 0;
    }
    return 1;
}

void random_generate()
{
    ll a,b,n,x0;
    a=673;
    b=727;
    n=997;
    x0=59;
    int iterations=0;
    ll first,second,ctr=0;
    while(ctr<2)
    {
        x0 = (a*x0 + b)%n;
        cout<<x0<<" ";
        iterations++;
        if(isPrime(x0))
        {
            if(ctr==0)
                p=x0;
            else if(ctr==1)
                q=x0;
            ctr++;
        }
    }
    cout<<"\nNo of iterations for generating p and q: ";
    cout<<iterations<<"\n";
    cout<<"\np= "<<p<<" q= "<<q<<"\n";
}

ll gcd(ll x,ll y)
{
    return y==0 ? x : gcd(y,x%y);
}


ll mult_inv(ll x,ll y)
{

    ll r , q , s1=0 , s2=1 , s3;         // s =1,0  // t= 0,1 a*s + b*t
    ll mod=y;

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
    ll ans;
    if(s1<0)
        ans=(s1+mod)%mod;
    else
        ans=s1%mod;

    return ans;
}

ll rsaUtil(ll plain,ll e,ll d,ll n)
{
    ll enc = 1;

    for(ll i=0;i<e;i++)
    {
        enc=((enc%n)*(plain%n))%n;
    }

    ll dec=1;
    for(ll i=0;i<d;i++)
    {
        dec=((dec%n)*(enc%n))%n;
    }
    cout<<"\nDecrypted= "<<dec<<"\n";
    if(dec==plain)
        cout<<"\n\nBoth Decrypted and Plain text are same\n\n"; // to check our program is correct

    return enc;
}

ll rsa(ll plain)
{
    ll n = p * q;
    ll phi = (p-1) * (q-1);
    ll e;
    for(ll i=2;i<phi;i++)
    {
        if(gcd(i,phi)==1)
        {
            e=i;
            break;
        }
    }

    ll d=mult_inv(e,phi);

    ll encrypted;

    cout<<"\ne= "<<e<<" d= "<<d<<" n= "<<n<<" phi= "<<phi<<"\n";
    encrypted=rsaUtil(plain,e,d,n);
    return encrypted;
}

int main()
{
    random_generate();

    ll plain;
    cout<<"\nEnter the number to be encrypted: ";
    cin>>plain;

    ll encrypted=rsa(plain);
    cout<<"\nEncrypted Text: "<<encrypted;
}




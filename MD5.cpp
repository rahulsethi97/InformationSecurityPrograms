#include<bits/stdc++.h>
using namespace std;

int msg[100007];  // to binary form of our message

//-----Declaration of constants------------/


unsigned int A=0x01234567,B=0x89ABCDEF,C=0xFEDCBA98,D=0x76543210;
unsigned int a,b,c,d;
unsigned int shift[4][4]={{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}};
unsigned int P[4],temp;
unsigned int t[65];

//-----------------------------------/

void initialise()
{
t[1]=0xd76aa478;
t[2]=0xe8c7b756;
t[3]=0x242070db;
t[4]=0xc1bdceee;
t[5]=0xf57c0faf;
t[6]=0x4787c62a;
t[7]=0xa8304613;
t[8]=0xfd469501;
t[9]=0x698098d8;
t[10]=0x8b44f7af;
t[11]=0xffff5bb1;
t[12]=0x895cd7be;
t[13]=0x6b901122;
t[14]=0xfd987193;
t[15]=0xa679438e;
t[16]=0x49b40821;
t[17]=0xf61e2562;
t[18]=0xc040b340;
t[19]=0x265e5a51;
t[20]=0xe9b6c7aa;
t[21]=0xd62f105d;
t[22]=0x2441453;
t[23]=0xd8a1e681;
t[24]=0xe7d3fbc8;
t[25]=0x21e1cde6;
t[26]=0xc33707d6;
t[27]=0xf4d50d87;
t[28]=0x455a14ed;
t[29]=0xa9e3e905;
t[30]=0xfcefa3f8;
t[31]=0x676f02d9;
t[32]=0x8d2a4c8a;
t[33]=0xfffa3942;
t[34]=0x8771f681;
t[35]=0x6d9d6122;
t[36]=0xfde5380c;
t[37]=0xa4beea44;
t[38]=0x4bdecfa9;
t[39]=0xf6bb4b60;
t[40]=0xbebfbc70;
t[41]=0x289b7ec6;
t[42]=0xeaa127fa;
t[43]=0xd4ef3085;
t[44]=0x4881d05;
t[45]=0xd9d4d039;
t[46]=0xe6db99e5;
t[47]=0x1fa27cf8;
t[48]=0xc4ac5665;
t[49]=0xf4292244;
t[50]=0x432aff97;
t[51]=0xab9423a7;
t[52]=0xfc93a039;
t[53]=0x655b59c3;
t[54]=0x8f0ccc92;
t[55]=0xffeff47d;
t[56]=0x85845dd1;
t[57]=0x6fa87e4f;
t[58]=0xfe2ce6e0;
t[59]=0xa3014314;
t[60]=0x4e0811a1;
t[61]=0xf7537e82;
t[62]=0xbd3af235;
t[63]=0x2ad7d2bb;
t[64]=0xeb86d391;

}

void last64Bit(string message,int n)
{
    int len=message.size();
    int pos=64;
    int lower=n-64;;
    int ascii_value=len*8;

        while((ascii_value)>0)
        {
            msg[lower+pos]=ascii_value%2;
            ascii_value/=2;
            pos--;
        }

}

void toBinaryAndPadding(string message,int n) // this function converts our message to binary do necessary padding
{
    int len=message.size();
    int pos=7;
    int lower=0;
    int ascii_value;
    for(int i=0;i<len;i++)
    {
        ascii_value=message[i];

        while((ascii_value)>0)
        {
            msg[lower+pos]=ascii_value%2;
            ascii_value/=2;
            pos--;
        }
        pos=7;
        lower=lower+8;
    }
    msg[len*8]=1; //first bit padded all others are zero

    last64Bit(message,n);
}



void toHex(unsigned int x)
{
    int arr[32];
    memset(arr,0,sizeof(arr));
    int pos=31;
    while(x>0)
    {
        arr[pos]=x%2;
        x=x/2;
        pos--;
    }
    pos=31;
    while(pos>=0)
    {
       int t=0,power=0;
       for(int i=0;i<4;i++)
       {
           t += arr[pos]*pow(2,power);
           power++;
           pos--;
       }
       if(t<10)
        cout<<t;
       else
       {
           switch(t)
           {
            case 10:
                cout<<"A";
                break;
            case 11:
                cout<<"B";
                break;
            case 12:
                cout<<"C";
                break;
            case 13:
                cout<<"D";
                break;
            case 14:
                cout<<"E";
                break;
            case 15:
                cout<<"F";
                break;
           }
       }

    }
}

unsigned int circShift(unsigned int x,int amount)
{
    int arr[32];
    int arr_duplicate[32];
    memset(arr,0,sizeof(arr));
    int pos=31;
    while(x>0)
    {
        arr[pos]=x%2;
        x=x/2;
        pos--;
    }

    for(int i=0;i<32;i++)
    {
        arr_duplicate[i]=arr[(i+amount)%32];
    }
    unsigned int ret=0;
    int power=0;
    for(int i=31;i>=0;i--)
    {
        ret += arr_duplicate[i]*pow(2,power);
        power++;
    }

    return ret;
}

void iterations(int x)
{
    int m=0;


    int k=1;
    for(int msg_iterator=0;msg_iterator<x;msg_iterator++) // for each 512 block
    {
        for(int i=0;i<4;i++) // for 4 rounds of iterations
        {
            //---P[i] functions---/
            P[0]=(B&C)|((!B)&D);
            P[1]=(B&D)|(C&(!D));
            P[2]=B^C^D;
            P[3]=C^(B|(!D));
            //--------------------/
            a=A,b=B,c=B,d=D;
            for(int j=1;j<16;j++)
            {
                unsigned int msg32=0;

                int pos = 512*msg_iterator + j*32 -1;
                int power=0;
                while(pos >= (512*msg_iterator +(j-1)*32) )
                {

                    msg32 += msg[pos]*pow(2,power);
                    power++;
                    pos--;
                }

                unsigned mid=(P[i] + a + msg32 + t[k]);

                mid=circShift(mid,shift[i][(j-1)/4]);

                a=d;
                d=c;
                c=b;
                b=b+mid;
                k++;
            }
            A=a+A;
            B=b+B;
            C=c+C;
            D=d+D;
        }

    }
    toHex(A);cout<<" ";toHex(B);cout<<" ";toHex(C);cout<<" ";toHex(D);cout<<" ";

}


void md5(string message)
{
    int len=message.size();
    int x=0;
    while((512*x -64)<=len*8)
    {
        x++;
    }

    int message_size=512*x;

    toBinaryAndPadding(message,message_size);
    iterations(x);
}

int main()
{
    initialise();
    string message;
    cout<<"\nEnter the Message: ";
    cin>>message;
    md5(message);
}

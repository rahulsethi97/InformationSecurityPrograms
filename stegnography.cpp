#include<bits/stdc++.h>
using namespace std;

int arr[8];

void convert_to_binary(int x)
{
	int pos=7;
	while(x>0)
	{
	arr[pos]=x%2;
	x=x/2;
	pos--;
	}
}


int bin_to_dec()
{
	int ans=0,power=0;

	for(int i=7;i>=0;i--)
		{
			if(arr[i]==1)
			   ans+=pow(2,power);
		power++;
		}
	return ans;
}

int main()
{
	fstream read;
	read.open("readable_lab1.txt");

	fstream encrypt;
	encrypt.open("encrypted_lab1.txt");
	encrypt<<"$";

 	char ch;
 	int dec;
	int temp=32;
	char out=32;

	while(!read.eof())
	{
		read.get(ch);
		cout<<ch;
		dec=ch;
		cout<<dec<<" ";
		convert_to_binary(dec);


	    for(int i=0;i<8;i++)
		{
		cout<<arr[i];
		if(arr[i]==1)
			encrypt<<out<<out;
		else
			encrypt<<out;
		encrypt<<"$";
	    }
	    cout<<"\n";
	}
	read.close();
    encrypt.close();

	fstream decrypt;
	decrypt.open("decrypted_lab1.txt");
    encrypt.open("encrypted_lab1.txt");

    cout<<"\n\nEncrypted Text: ";
	int size=270;
	int pos=0,prev=0;
	while(!encrypt.eof())
	{
		size--;

		encrypt.get(ch);
		cout<<ch;
		dec=ch;
		if(dec==32)
		{
			if(prev==1)
			{
				arr[pos]=1;
				pos++;
				prev=0;
			}
			else
			 prev++;
		}
		else
		{
			if(prev==1)
			{
				arr[pos]=0;
				pos++;
				prev=0;
			}
		}
		if(pos==8)
		{
		//for(int i=0;i<8;i++)
			//cout<<arr[i]<<" ";
			pos=0;
			dec=bin_to_dec();
			if(dec==96)
				dec=32;
			cout<<dec<<" ";

			ch=dec;
			cout<<ch<<"\n";
			decrypt<<ch;
		}
	if(size==0)
        break;
	}

	decrypt.close();

	decrypt.open("decrypted_lab1.txt");

    cout<<"\n\nDecrypted Text: ";
    while(!decrypt.eof())
	{
		decrypt.get(ch);
		cout<<ch;
	}

	decrypt.close();
	encrypt.close();



}

#include<bits/stdc++.h>
using namespace std;


int main()
{
    cout<<"\nEnter the number of rails: ";
	int k;
	cin>>k;

    fstream read;
	read.open("railfence_readable.txt");

	fstream encrypt;
	encrypt.open("railfence_encrypted.txt");

    fstream decrypt;
	decrypt.open("railfence_decrypted.txt");

	char ch;
	char plain[120];
	int size=0;

	//input readable file
	while(!read.eof())
	{
		read>>ch;
		plain[size]=ch;
		size++;
	}
	size--;
	//---------

	cout<<"\nText read from file: ";
	for(int i=0;i<size;i++)
		cout<<plain[i]<<" ";
		cout<<"\n\n";

	// Encryption starts
	char encrypted[size];


	int pos=0; // for insertion of element into decrypt array
	int dist,even_dist,odd_dist;
	int start,flag=1; // flag=1 for odd turn and 0 for even turn

	for(int i=0;i<k;i++)
	{
		encrypted[pos]=plain[i];
		pos++;

		start=i;
		flag=0;
		dist=2*(k-i-1); // Initial distance will always be of odd turn

		if(i==0 || i==(k-1))
		{
			dist= 2*(k-1);

			while((start+dist)<size)
			{
			encrypted[pos]=plain[start+dist];
			pos++;
			start=start+dist;
			}
		}
		else
		{
			while((start+dist)<size)
			{

			encrypted[pos]=plain[start+dist];
			pos++;
			start=start+dist;

			if(flag) // odd
			{
			 dist=2*(k-i-1);
			 flag=0;
			}
			else	// even
			{
			 dist=2*i;
			 flag=1;
			}

			}
		}
	}

	cout<<"\nEncrypted Text: ";
	for(int i=0;i<size;i++)
	{
		encrypt<<encrypted[i];
		cout<<encrypted[i]<<" ";
	}
	cout<<"\n\n";

	//	Encryption ends

	//  Decryption starts

	char decrypted[size];
	pos=0;
	for(int i=0;i<k;i++)
	{
		decrypted[i]=encrypted[pos];
		pos++;
		start=i;
		flag=0;
		dist=2*(k-i-1);

		if(i==0 || i==(k-1))
		{
			dist= 2*(k-1);

			while((start+dist)<size)
			{
			decrypted[start+dist]=encrypted[pos];
			pos++;
			start=start+dist;
			}
		}
		else
		{

			while((start+dist)<size)
			{
			decrypted[start+dist]=encrypted[pos];
			pos++;
			start=start+dist;


			if(flag) // odd
			{
			 dist=2*(k-i-1);
			 flag=0;
			}
			else	// even
			{
			 dist=2*i;
			 flag=1;
			}

			}
		}


	}


	cout<<"\nDecrypted Text: ";
	for(int i=0;i<size;i++)
	{
		decrypt<<decrypted[i];
		cout<<decrypted[i]<<" ";
	}
	cout<<"\n\n";

	// decryption ends

	decrypt.close();
	encrypt.close();
	read.close();


}

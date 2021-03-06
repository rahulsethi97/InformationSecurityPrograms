#include<bits/stdc++.h>
using namespace std;

#define mat_size 8
char mat[mat_size][mat_size];
int hash[256];
int pos[256][2];


void build_matrix(string key)
{
	int n=key.size();
	int i=0,j=0;
	for(int k=0;k<n;k++)
		{
		 if(hash[key[k]]==0)
		 {

		 	/*//-- for i and j
		 	if(key[k]=='i' && hash[9]>0)
		 		continue;
		 	if(key[k]=='j' && hash[8]>0)
		 		continue;
		 	//--*/

		 	mat[i][j]=key[k];
		 	hash[key[k]]++;

		 	j=(j+1)%mat_size;
		 	if(j==0)
		 		i++;

		 }
		}

	for(int k=0;k<256;k++)
	{
		if(hash[k]==0 && ( (k>='a' && k<='z') || (k>='A' && k<='Z') || (k>='0' && k<='9')  ) )
		{
			/*//--- for i and j
			if(k==8 && hash[9]>0)
		 		continue;
		 	if(k==9 && hash[8]>0)
		 		continue;
		 	//---*/

			char ch=k;
			mat[i][j]=ch;
		 	hash[k]++;
		 	j=(j+1)%mat_size;
		 	if(j==0)
		 		i++;
		}
	}

	mat[7][6]=mat[7][7]='#';

}

void build_pos_array()
{
	// this array contains the position of characters in matrix
	for(int i=0;i<256;i++)
		pos[i][0]=pos[i][1]=0;

	for(int i=0;i<mat_size;i++)
	{
		for(int j=0;j<mat_size;j++)
		{
			pos[ mat[i][j] ][0]=i;
			pos[ mat[i][j] ][1]=j;
		}
	}

}

void show_matrix()
{
	for(int i=0;i<mat_size;i++)
	{
		for(int j=0;j<mat_size;j++)
			cout<<mat[i][j]<<" ";
			cout<<"\n";
	}


}

int main()
{
    cout<<"\nEnter the key: ";
	string key;
	cin>>key;

	build_matrix(key);
	build_pos_array();
	show_matrix();


	fstream read;
	read.open("playfair_modified_readable.txt");

	fstream encrypt;
	encrypt.open("playfair_modified_encrypted.txt");

    fstream decrypt;
	decrypt.open("playfair_modified_decrypted.txt");

	char ch;
	char plain[120];
	int size=0;
	while(!read.eof())
	{
		read>>ch;
		plain[size]=ch;
		size++;
	}
	size--;
	//---------

	for(int i=1;i<size;i++)
	{
		if(plain[i]==plain[i-1])
			{
				size=size+2;
				for(int j=size-1;j>=i+2;j--)
					plain[j]=plain[j-2];

				plain[i]='z';
				plain[i+1]='z';
			}
	}

	if(size%2!=0)
	{
		plain[size]='z';
		size++;
	}
	//-----------

	cout<<"\nText Read from file: ";
	for(int i=0;i<size;i++)
		cout<<plain[i];
		cout<<"\n\n";

	char encrypted[120];
	int size_en=0;

	for(int i=0;i<size;i=i+2)
	{
		char ch1,ch2;
		ch1=plain[i];
		ch2=plain[i+1];

		//cout<<ch1<<" "<<ch2<<" ";
		int t1=ch1;
		int t2=ch2;

		//cout<<t1<<" "<<t2<<" ";

		int x1=pos[t1][0];
		int y1=pos[t1][1];

		int x2=pos[t2][0];
		int y2=pos[t2][1];

		//cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";

		if((x1!=x2) && (y1==y2))  // same column
		{
			x1=(x1+1)%mat_size;
			x2=(x2+1)%mat_size;
			encrypt<<mat[x1][y1];
			encrypted[size_en]=mat[x1][y1];
			size_en++;
			encrypt<<mat[x2][y2];
			encrypted[size_en]=mat[x2][y2];
			size_en++;
		}
		else if( (x1==x2) && (y1!=y2) ) // same row
		{
			y1=(y1+1)%mat_size;
			y2=(y2+1)%mat_size;

			encrypt<<mat[x1][y1];
			encrypted[size_en]=mat[x1][y1];
			size_en++;
			encrypt<<mat[x2][y2];
			encrypted[size_en]=mat[x2][y2];
			size_en++;
		}
		else // diff row and diff column
		{
			encrypt<<mat[x1][y2];
			encrypted[size_en]=mat[x1][y2];
			size_en++;
			encrypt<<mat[x2][y1];
			encrypted[size_en]=mat[x2][y1];
			size_en++;
		}
	}

	cout<<"\nEncrypted Text: ";
	for(int i=0;i<size_en;i++)
		cout<<encrypted[i];
		cout<<"\n\n";

	// Decryption Starts

	char decrypted[120];
	int size_de=0;

	for(int i=0;i<size_en;i=i+2)
	{
		char ch1,ch2;
		ch1=encrypted[i];
		ch2=encrypted[i+1];

		int t1=ch1;
		int t2=ch2;

		//cout<<ch1<<" "<<ch2<<" ";

		int x1=pos[t1][0];
		int y1=pos[t1][1];

		int x2=pos[t2][0];
		int y2=pos[t2][1];

		//cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
		if((x1!=x2) && (y1==y2))  // same column
		{
			x1=(x1-1 + mat_size)%mat_size;
			x2=(x2-1 + mat_size)%mat_size;

			decrypt<<mat[x1][y1];
			decrypted[size_de]=mat[x1][y1];
			size_de++;

			decrypt<<mat[x2][y2];
			decrypted[size_de]=mat[x2][y2];
			size_de++;
		}
		else if( (x1==x2) && (y1!=y2) ) // same row
		{
			y1=(y1-1+mat_size)%mat_size;
			y2=(y2-1+mat_size)%mat_size;
			decrypt<<mat[x1][y1];
			decrypted[size_de]=mat[x1][y1];
			size_de++;

			decrypt<<mat[x2][y2];
			decrypted[size_de]=mat[x2][y2];
			size_de++;
		}
		else // diff row and diff column
		{
			decrypt<<mat[x1][y2];
			decrypted[size_de]=mat[x1][y2];
			size_de++;

			decrypt<<mat[x2][y1];
			decrypted[size_de]=mat[x2][y1];
			size_de++;
		}
	}

	cout<<"\nDecrypted Text: ";
	for(int i=0;i<size_de;i++)
		cout<<decrypted[i];
		cout<<"\n\n";

	decrypt.close();
	encrypt.close();
	read.close();


}

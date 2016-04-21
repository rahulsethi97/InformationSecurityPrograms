#include<bits/stdc++.h>
using namespace std;

int pos[120];
char mat[120][120];


void build_pos(string key) // to build the position array for reading the column
{
	int ascii[key.size()];
	int n=key.size();
	for(int i=0;i<n;i++)
		{
		ascii[i]=key[i];
		pos[i]=ascii[i];
		}

	sort(ascii,ascii+n);

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(pos[j]==ascii[i])
				pos[j]=i;
		}
	}

	//for(int i=0;i<n;i++)
	//	cout<<pos[i]<<" ";

}


int find_col(int x,int n)  // called to find the next column needed
{
	for(int i=0;i<n;i++)
		if(pos[i]==x)
			return i;
}

int main()
{
	fstream read;
	read.open("columnar_readable.txt");

	fstream encrypt;
	encrypt.open("columnar_encrypted.txt");

    fstream decrypt;
	decrypt.open("columnar_decrypted.txt");

	//--- Reading from File

	char plain[120],ch;
	int size=0;
	while(!read.eof())
	{
		read>>ch;
		plain[size]=ch;
		size++;
	}
	size--; // cin read extra character so size--

	//---

	cout<<"\nText read from file: ";
	for(int i=0;i<size;i++)
		cout<<plain[i];
	    cout<<"\n\n";

	string key;
	cout<<"Enter the key to encrypt this file: ";
	cin>>key;

	build_pos(key); // function call to make a position array according to the key


	//--- Finding the dimensions of the matrix
	int block_size=key.size();
	int row=ceil((double)size/(double)block_size);
	//----
	int pos_in_string=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<block_size;j++)
		{
			if(pos_in_string<size)
			{
				mat[i][j]=plain[pos_in_string];
				pos_in_string++;
			}
			else
			{
				mat[i][j]='z';
			}
		}
	}

	for(int i=0;i<block_size;i++)
		cout<<pos[i]<<" ";
		cout<<"\n";

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<block_size;j++)
			{
			cout<<mat[i][j]<<" ";
			}
			cout<<"\n";
	}


	char encrypted[120];
	int size_en=0;

	int col_desired=0;
	int curr_col=find_col(col_desired,block_size);
	int temp=block_size;

	while(temp--)
	{
		for(int j=0;j<row;j++)
		{
			encrypted[size_en]=mat[j][curr_col];
			encrypt<<mat[j][curr_col];
			size_en++;
		}
		col_desired++;
		curr_col=find_col(col_desired,block_size);
	}

	cout<<"\nEncrypted Text: ";
	for(int i=0;i<size_en;i++)
		cout<<encrypted[i];
		cout<<"\n";


	//Decryption starts

	char dec_mat[120][120];
	col_desired=0;
	curr_col=find_col(col_desired,block_size);
	temp=block_size;
	int position=0;
	while(temp--)
	{
		for(int j=0;j<row;j++)
		{
			dec_mat[j][curr_col]=encrypted[position];
			position++;
		}

		col_desired++;
		curr_col=find_col(col_desired,block_size);
	}

	cout<<"\nMatrix after decryption\n\n";

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<block_size;j++)
		{
			cout<<dec_mat[i][j]<<" ";
		}
		cout<<"\n";
	}

	cout<<"\nAfter reading row by row: ";
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<block_size;j++)
		{
			if(mat[i][j]=='z' && mat[i][j+1]=='z') // to avoid bogus letters
			 break;

			cout<<mat[i][j];
			decrypt<<mat[i][j];
		}

	}


}

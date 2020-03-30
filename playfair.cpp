#include<iostream>
#include<string>
#include<vector>
using namespace std;
void generate_key_square(string key, char KT[5][5]);
string make_even(string s);
void encrypt(string s, char KT[5][5]);

string lower(string s)
{
	string lower="";
	for(int i=0;i<s.length();i++)
	{
		lower+=tolower(s[i]);
	}
	return lower;
}
string make_even(string s)
{
	int length=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]!=' ')
		{
			length++;
		}
	}
	if(length%2!=0)
	{
		s.append("z");
	}
	return s;
}

void generate_key_square(string key, char KT[5][5])
{
	int visit[26];
	int i,j,k;
	string enc_str;
	for(k=0;k<26;k++)
	{
		if((char)(k+97) != 'j')
			visit[k]=1;
	}
	for(k=0;k<key.length();k++)
	{
		visit[key[k]-97]=0;
	}
	i=0;
	j=0;
	for(int l=0;l<key.length();l++)
	{
		if(visit[key[l]-97]==0)
		{
			visit[key[l]-97]=-1;
			KT[i][j]=key[l];
			j++;
			if(j==5)
			{
				i++;
				j=0;
			}
		}
	}
	for(k=0;k<26;k++)
	{
		if(visit[k]==1)
		{
			KT[i][j]=(char)(k+97);
			j++;
			if(j==5)
			{
				i++;
				j=0;
			}
		}
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			cout<<KT[i][j]<<" ";
		}
		cout<<endl;
	}
}

void encrypt(string s, char KT[5][5])
{
	int i,j,k;
	int x1,y1,x2,y2;
	string enc_str="";
	for(i=0;i<s.length();i+=2)
	{
		if(s[i] != ' ')
		{
			int count=i;
			for(j=0;j<5;j++)
			{
				for(k=0;k<5;k++)
				{
					if(KT[j][k]==s[count])
					{
						x1=j;
						y1=k;
					}
					else if(KT[j][k]==s[count+1])
					{
						x2=j;
						y2=k;
					}
				}
			}
			if(x1==x2) //same row
			{
				enc_str+=(KT[x1][(y1+1)%5]);
				enc_str+=(KT[x1][(y2+1)%5]);
			}
			else if(y1==y2) //same column
			{
				enc_str+=(KT[(x1+1)%5][y1]);
				enc_str+=(KT[(x2+1)%5][y1]);
			}
			else  
			{
				enc_str+=(KT[x1][y2%5]);
				enc_str+=(KT[x2%5][y1]);
			}
		}
	}
	cout<<enc_str<<endl;	
}

int main()
{
	string key;
	string s;
	cout<<"Enter Secret Key: ";
	cin>>key;
	cout<<"Enter string: ";
	cin >> ws; 
	getline(cin,s);
	char KT[5][5];
	string low_key=lower(key);
	generate_key_square(low_key,KT);
	string even = make_even(s);
	string low_case=lower(even);
	cout<<even<<endl;
	encrypt(low_case,KT);
	return 0;
}



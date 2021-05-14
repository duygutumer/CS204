#include<iostream>
#include<string>
#include<vector>

using namespace std;

void P(unsigned char & c)
{
	unsigned char array[8];
	//for seventh bit
	array[7] = (1 << 7) & c;
	array[7] = array[7] >> 2;
	//for sixth bit
	array[6] = (1 << 6) & c;
	array[6] = array[6] << 1;
	//for fifth bit
	array[5] = (1 << 5) & c;
	array[5] = array[5] >> 1;
	//for fourth bit
	array[4] = (1 << 4) & c;
	array[4] = array[4] << 2;
	//for third bit
	array[3] = (1 << 3) & c;
	array[3] = array[3] >> 2;
	//for second bit
	array[2] = (1 << 2) & c;
	array[2] = array[2] << 1;
	//for first bit
	array[1] = (1 << 1) & c;
	array[1] = array[1] >> 1;
	//for zeroth bit
	array[0] = 1 & c;
	array[0] = array[0] << 2;

	unsigned char result = 0;
	for(int i = 0; i < 8 ; i++)
	{
		result = result | array[i];
	}
	c = result;
}

void takingFromPlaintext(string & plaintext, string & newkey, vector<unsigned char> & listy)
{
	for(int i = 0; i < plaintext.length(); i++)
	{
		unsigned char c = plaintext[i];
		P(c); // changing each char using permutation 
		unsigned char kc = newkey[i];
		c = c ^ kc;
		listy[i] = c; // putting it to the vector
	}
}

string keyForPlintext(string & key, string & plaintext)
{
	string newkey = "";
	int j = 0;
	for(int i = 0; i < plaintext.length(); i++)
	{
		if(j != key.length())
		{
			newkey += key[j];
			j++;
		}
		else
		{
			j = 0;
			newkey += key[j];
			j++;
		}

	}
	
	return newkey;
}

int main()
{
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;

	string key, plaintext, newkey;

	cout << "Please enter the encryption key: ";
	getline(cin,key); //just once it asks

	cout << "Please enter the plaintext to be encrypted: ";
	while(getline(cin,plaintext))
	{
		
		newkey = keyForPlintext(key,plaintext);
		// cout << "new key: " << newkey << endl; 
		int size  = plaintext.length();
		vector<unsigned char> listy(size);
		takingFromPlaintext(plaintext, newkey, listy);
		cout << "Ciphertext: ";
		for(int i = 0; i < listy.size(); i++)
		{
			cout << hex << (int) listy[i];
		}
		cout << endl;
		cout << endl;
		cout << "Please enter the plaintext to be encrypted: ";
	}
	
	return 0;	
}



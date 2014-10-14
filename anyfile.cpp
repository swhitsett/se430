#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

//Crypto++ lib files
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
using namespace std;

string encrypt_file(string);
string decrypt_file(string);

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // cout this to see what it is.
byte iv[ CryptoPP::AES::BLOCKSIZE ];

int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		cout<<"here1"<<endl;
		string line;
		ifstream myfile (argv[1]);
		ofstream inputFile ("asdf.jpg");
		if(myfile.is_open())
		{
			cout<<"here2"<<endl;
			myfile.is_open();
			cout<<"here3"<<endl;
			while(getline(myfile, line))
				inputFile << decrypt_file(line) <<"\n";

cout<<"herea3"<<endl;
			inputFile.close();
			myfile.close();
cout<<"herea4"<<endl;
		}
		//decrypt_file(argv[1]);
	}
	else if(argc == 3)
	{
		string line;
		ifstream myfile (argv[1]);
		ofstream inputFile (argv[2]);
		if(myfile.is_open())
		{
			myfile.is_open();
			while(getline(myfile, line))
				inputFile << encrypt_file(line) <<"\n";

			inputFile.close();
			myfile.close();

		}
	}
	return 0;
}
string encrypt_file(string data)
{
	string plaintext = data;
	string ciphertext;
	ofstream aes_file;

	memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
	stfEncryptor.MessageEnd();

	return ciphertext;
	// aes_file.open("Locked_file.txt");
	// aes_file << ciphertext;
	// aes_file.close();

}

string decrypt_file(string data)
{

	string ciphertex = data;
	string decryptedtext;
	cout<<"daum!!"<<endl;
	// ifstream created_file("Locked_file.txt");
	// ofstream unlocked_file;

	// created_file.is_open();
	// getline(created_file, ciphertex);
	// created_file.close();

	//cout<<decryptedtext<<endl;
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertex.c_str() ), ciphertex.size() );
	stfDecryptor.MessageEnd();

	// unlocked_file.open("Locked_file.txt");
	// unlocked_file << decryptedtext;
	// unlocked_file.close();
	return decryptedtext;
}


		// ifstream myfile (argv[1]);
		// ofstream inputFile (argv[2]);
// if(myfile.is_open())
// 	{
// 		myfile.is_open();
// 		while(getline(myfile, line))
// 			inputFile << encrypt_file(line) <<"\n";

// 		inputFile.close();
// 		myfile.close();

// 	}
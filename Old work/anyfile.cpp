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

byte* encrypt_file(byte*);
string decrypt_file(string);

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // cout this to see what it is.
byte iv[ CryptoPP::AES::BLOCKSIZE ];

int main(int argc, char* argv[])
{
	if(argc == 2)
	{
		string line;
		ifstream myfile (argv[1], ios::binary);
		ofstream inputFile ("asdf.jpg");
		if(myfile.is_open())
		{
			getline(myfile, line);
			cout<<line<<endl;
			myfile.is_open();
			while(getline(myfile, line))
				inputFile << decrypt_file(line) <<"\n";

			inputFile.close();
			myfile.close();
		}
		//decrypt_file(argv[1]);
	}
	else if(argc == 3)
	{
		// ifstream myfile (argv[1], ifstream::binary);

		// myfile.seekg(0, myfile.end);
		// int length = myfile.tellg();
		// myfile.seekg(0, myfile.beg);

		// byte *buffer = new byte[length];
		// myfile.read(buffer,length);
		// encrypt_file(buffer);
		// string line;
		// ifstream myfile (argv[1]);
		// ofstream inputFile (argv[2]);
		// if(myfile.is_open())
		// {
		// 	myfile.is_open();
		// 	while(getline(myfile, line))
		// 		inputFile << encrypt_file(line) <<"\n";

		// 	inputFile.close();
		// 	myfile.close();

		// }
	}
	return 0;
}
byte* encrypt_file(byte* data)
{
	byte* plaintext = data;
	byte* ciphertext;
	//ofstream aes_file;

	memset( key, 0x00, CryptoPP::AES::MAX_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::ArraySink( ciphertext, sizeof(ciphertext) ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned byte*>( plaintext ), sizeof(plaintext) + 1 );
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
	//cout<<"daum!!"<<endl;
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
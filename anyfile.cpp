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
void decrypt_file();

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // cout this to see what it is.
byte iv[ CryptoPP::AES::BLOCKSIZE ];

int main(int argc, char* argv[])
{
	string line;
	ofstream myfile (argv[1]);
	ifstream inputFile (argv[2]);
	if(inputFile.is_open())
	{
		myfile.is_open();
		while(getline(inputFile, line))
			myfile << encrypt_file(line) <<"\n";
		inputFile.close();
		myfile.close();

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

void decrypt_file(string fileName)
{
	string ciphertex;
	string decryptedtext;

	ifstream created_file(fileName);
	ofstream unlocked_file;

	while(created_file.is_open())
	{
		getline(created_file, ciphertex);
		created_file.close();

		cout<<decryptedtext<<endl;
		CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

		CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
		stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertex.c_str() ), ciphertex.size() );
		stfDecryptor.MessageEnd();

		unlocked_file.open(fileName);
		unlocked_file << decryptedtext;
		// unlocked_file.close();
	}
	unlocked_file.close();
}
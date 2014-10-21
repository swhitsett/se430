#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <cstdlib>
using std::exit;

#include "cryptopp/files.h"
using CryptoPP::FileSource;
using CryptoPP::FileSink;

#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;

#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
// using CryptoPP::StreamTransformationFilter;
 using CryptoPP::AuthenticatedEncryptionFilter;

#include <cryptopp/eax.h>
using CryptoPP::EAX;

#include "cryptopp/aes.h"
using CryptoPP::AES;
//using CryptoPP::Blowfish;

#include "cryptopp/modes.h"

using CryptoPP::CFB_Mode;
using namespace std;

string encrypt_file(string);
string decrypt_file(string);

byte key[ CryptoPP::AES::MAX_KEYLENGTH ]; // cout this to see what it is.
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
		string line;

		ifstream myfile (argv[1], ifstream::binary);
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

string encrypt_file(string oData)
{
	string plaintext = oData;
	string ciphertext;
	//ofstream aes_file;

	memset( key, 0x00, CryptoPP::AES::MAX_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::MAX_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
	stfEncryptor.MessageEnd();

	return ciphertext;
	// aes_file.open("Locked_file.txt");
	// aes_file << ciphertext;
	// aes_file.close();
}

string decrypt_file(string eData)
{
	string ciphertex = eData;
	string decryptedtext;

	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::MAX_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertex.c_str() ), ciphertex.size() );
	stfDecryptor.MessageEnd();

	// unlocked_file.open("Locked_file.txt");
	// unlocked_file << decryptedtext;
	// unlocked_file.close();
	return decryptedtext;
}
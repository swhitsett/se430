#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

//Crypto++ lib files
// #include "cryptopp/modes.h"
// #include "cryptopp/aes.h"
// #include "cryptopp/filters.h"
// #include "cryptopp/osrng.h"
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
// using CryptoPP::AuthenticatedEncryptionFilter;

#include "cryptopp/aes.h"
using CryptoPP::AES;
//using CryptoPP::Blowfish;

#include "cryptopp/modes.h"

using CryptoPP::CFB_Mode;
using namespace std;

void encrypt_file(string,string);
void decrypt_file(string,string);

int main(int argc, char* argv[])
{
	if(argv[1] == 'e')
	{
		string originalFile = argv[2];
		string encryptedFile = argv[2];
		encryptedFile = encryptedFile+"e";
		encrypt_file(originalFile,encryptedFile);
	}
	else if(argv[1] == 'd')
	{
		string encryptedFile = argv[2];
		string decryptedFile = encryptedFile.substr(0,encryptedFile.size()-1); // remove e
		decrypt_file(encryptedFile,decryptedFile);
	}
	return 0;
}

void encrypt_file(string originalName, string encryptedName)
{
	AutoSeededRandomPool prng;

	byte key[AES::DEFAULT_KEYLENGTH];// byte key(Blowfish::DEFAULT_KEYLENGTH);
	prng.GenerateBlock( key, sizeof(key) );//prng.GenerateBlock( key, key.size() );

	byte iv[ AES::BLOCKSIZE ];
	prng.GenerateBlock( iv, sizeof(iv) );

	CFB_Mode< AES >::Encryption e1;//EAX< Blowfish >::Encryption e1;
   e1.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));

   FileSource fs1(originalName.c_str(), true, StreamTransformationFilter(e1,new FileSink(encryptedName.c_str())) );

}

void decrypt_file(string encryptedName, string decryptedName)
{
	// EAX< Blowfish >::Decryption d2;
 //    d2.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );

 //    FileSource fs2(encryptedName.c_str(), true,new AuthenticatedDecryptionFilter( d2,new FileSink( decryptedName.c_str() ),AuthenticatedDecryptionFilter::THROW_EXCEPTION) );
}
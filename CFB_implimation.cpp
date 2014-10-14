// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

#include "cryptopp/osrng.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
int main()
{
	//AutoSeededRandomPool prng;

	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
	GenerateBlock(key, sizeof(key));

	// prng.GenerateBlock(key, sizeof(key));

	byte iv[CryptoPP::AES::BLOCKSIZE];
	GenerateBlock(iv, sizeof(iv));

	string plain_text = "CFB Mode Test";
	string cipher, encoded, recovered;


	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,new HexEncoder(new StringSink(encoded))); // StringSource
	cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,new HexEncoder(new StringSink(encoded))); // StringSource
	cout << "iv: " << encoded << endl;


	try
	{
		cout << "plain text: " << plain_text << endl;

		CryptoPP::CFB_Mode< AES >::Encryption.SetKeyWithIV(key, sizeof(key), iv);

		// CFB mode must not use padding. Specifying
		//  a scheme will result in an exception
		StringSource(plain_text, true, new StreamTransformationFilter(CryptoPP::CFB_Mode< AES >::Encryption ,new StringSink(cipher))); // StringSource
	}

	// Pretty print
	encoded.clear();
	StringSource(cipher, true,new HexEncoder(new StringSink(encoded))); // StringSource
	cout << "cipher text: " << encoded << endl;

	try
	{
		CryptoPP::CFB_Mode< AES >::Decryption.SetKeyWithIV(key, sizeof(key), iv);
		StringSource s(cipher, true,new StreamTransformationFilter(d,new StringSink(recovered))); 

		cout << "recovered text: " << recovered << endl;
	}
	return 0;
}


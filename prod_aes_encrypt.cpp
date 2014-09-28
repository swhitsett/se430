// A quick run at encryption using AES and crypto++ library
#include <iostream>
#include <iomanip>
#include <fstream>

//Crypto++ lib files
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"

using namespace std;

void encrypt_file(string);
void decrypt_file();
int main()
{
   //if credentials form ARM board are valid ...
   int usr_choice;
   bool Exit_test = false;
   while(Exit_test != true)
   {
	   cout<<"Encrypt[1]\nDecrypt[2]\nQuit[0]";
	   cin>>usr_choice;

	   if(usr_choice == 1)
	   {
	   	string provided_data;  // change to int
	   	cout<<"Enter data: ";
	   	cin>>provided_data;
	   	encrypt_file(provided_data);
	   }
	   else if(usr_choice == 2)
	   {
	   	cout<<"decrypting file....."<<endl;
	   	decrypt_file();
	   }
	   else if(usr_choice == 0)
	   {
	   	Exit_test == true;
	   }
   }
	return 0;
}

void encrypt_file(string data)
{
	string plain_text = data;
	string encrypted_input;
	ofstream aes_file;

	byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // cout this to see what it is.
	byte iv[ CryptoPP::AES::BLOCKSIZE ];
	memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );


	cout << "Plain Text (" << plain_text.size() << " bytes)" << endl;
	cout << plain_text <<"\n"<<endl;


	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( encrypted_input ) );
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plain_text.c_str() ), plain_text.length() + 1 );
	stfEncryptor.MessageEnd();
	aes_file.open("create_file.txt");
	aes_file << encrypted_input;
	aes_file.close();
}

void decrypt_file()
{
	string file_contents;
	string decrypted_file_contents;

	byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ]; // cout this to see what it is.
	byte iv[ CryptoPP::AES::BLOCKSIZE ];
	memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
	memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

	ifstream created_file("create_file.txt");
	if(created_file.is_open())
	{
		getline(created_file, decrypted_file_contents);
		created_file.close();
	}

	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decrypted_file_contents ) );
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( file_contents.c_str() ), file_contents.size() );
	stfDecryptor.MessageEnd();

	//
	// Dump Decrypted Text
	//
	cout << "Decrypted Text: " << endl;
	cout << decrypted_file_contents;
	cout << endl << endl;
}
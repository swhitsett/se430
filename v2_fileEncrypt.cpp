// g++ -DDEBUG=1 -g3 -O0 -Wall -Wextra v2_fleEncrypt.cpp -o crypt -lcryptopp
// g++ -DNDEBUG=1 -g3 -O2 -Wall -Wextra cryptopp-test.cpp -o cryptopp-test.exe -lcryptopp
 
#include <iostream>
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::ios;
 
#include <string>
using std::string;
 
#include <vector>
using std::vector;
 
#include <algorithm>
using std::sort;
using std::less;
 
#include <fstream>
using std::ifstream;
 
#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;
using CryptoPP::PK_Encryptor;
using CryptoPP::PK_Decryptor;
 
#include <cryptopp/sha.h>
using CryptoPP::SHA256;
 
#include <cryptopp/secblock.h>
using CryptoPP::SecByteBlock;
 
#include <cryptopp/files.h>
using CryptoPP::FileSink;
using CryptoPP::FileSource;
 
#include <cryptopp/queue.h>
using CryptoPP::ByteQueue;
 
#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
 
#include <cryptopp/base64.h>
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;
 
#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::FileSink;
using CryptoPP::FileSource;
using CryptoPP::PK_EncryptorFilter;
using CryptoPP::PK_DecryptorFilter;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;
 
#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;
 
#include <cryptopp/integer.h>
using CryptoPP::Integer;
 
#include <cryptopp/dh.h>
using CryptoPP::DH;
 
#include <cryptopp/sha.h>
using CryptoPP::SHA1;
 
#include <cryptopp/modes.h>
using CryptoPP::CBC_Mode;
 
#include <cryptopp/eax.h>
using CryptoPP::EAX;
 
#include <cryptopp/tea.h>
using CryptoPP::TEA;
 
#include <cryptopp/blowfish.h>
using CryptoPP::AES;
 
#include <cryptopp/pssr.h>
using CryptoPP::PSS;
 
#include <cryptopp/rsa.h>
using CryptoPP::RSA;
using CryptoPP::RSASS;
 
#include <cryptopp/nbtheory.h>
using CryptoPP::ModularExponentiation;
 
#include <cryptopp/eccrypto.h>
using CryptoPP::ECDSA;
using CryptoPP::ECP;
 
#include <cryptopp/oids.h>
using CryptoPP::ASN1::secp521r1;
 
#include <cryptopp/modes.h>
#include <cryptopp/gzip.h>
#include <cryptopp/blowfish.h>
 
#include <cryptopp/rsa.h>
using CryptoPP::RSA;
using CryptoPP::InvertibleRSAFunction;
using CryptoPP::RSAES_OAEP_SHA_Encryptor;
using CryptoPP::RSAES_OAEP_SHA_Decryptor;
 
using CryptoPP::RSASSA_PKCS1v15_SHA_Signer;
using CryptoPP::RSASSA_PKCS1v15_SHA_Verifier;
 
using CryptoPP::Exception;
 
typedef CryptoPP::ECDSA<ECP, SHA256>::PrivateKey ECDSAPrivateKey;
typedef CryptoPP::ECDSA<ECP, SHA256>::PublicKey ECDSAPublicKey;
 
void encrypt_file(string);
void decrypt_file(string);

SecByteBlock key(AES::MAX_KEYLENGTH);
byte iv[ AES::BLOCKSIZE ];

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        encrypt_file(argv[2]);
        //decrypt_file("puppy-and-teddy.enc");
    }
    else if(argc == 2)
    {
        decrypt_file(argv[1]);
    }
    else
        std::cout<<"shit"<<endl;
    return 0;  

}
void encrypt_file(string oFile)
{
    // SecByteBlock key(AES::MAX_KEYLENGTH);
    // byte iv[ AES::BLOCKSIZE ];
   
    string ofilename = oFile;
    string outFile = "puppy-and-teddy.encf";
    string efilename = outFile.;//"puppy-and-teddy.enc";
    //string rfilename = "puppy-and-teddy-recovered.jpg";
   
    //try {
       
        /*********************************\
         \*********************************/
       
    EAX< AES >::Encryption e1;
    e1.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );
   
    std::ifstream ifile(oFile.c_str(), ios::binary);
    std::ifstream::pos_type size = ifile.seekg(0, std::ios_base::end).tellg();
    ifile.seekg(0, std::ios_base::beg);
   
    string temp;
    temp.resize(size);
    ifile.read((char*)temp.data(), temp.size());
   
    StringSource ss1( temp, true,
                    new AuthenticatedEncryptionFilter( e1,
                    new FileSink( efilename.c_str() )
                    ) // StreamTransformationFilter
                    ); // StringSource
   
    /*********************************\
     \*********************************/
}

void decrypt_file(string efile)
{   

    string efilename = efile;
    string rfilename = "puppy-and-teddy-recovered.jpg";

    //SecByteBlock key(AES::MAX_KEYLENGTH);
    //byte iv[ AES::BLOCKSIZE ];

    EAX< AES >::Decryption d2;
    d2.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );
   
    FileSource fs2( efilename.c_str(), true,
                    new AuthenticatedDecryptionFilter( d2,
                    new FileSink( rfilename.c_str() ),
                    AuthenticatedDecryptionFilter::THROW_EXCEPTION
                    ) // StreamTransformationFilter
                    ); // StringSource
}
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

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

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
using CryptoPP::Blowfish;

#include "cryptopp/modes.h"
#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

using CryptoPP::CFB_Mode;
using namespace std;

using namespace std;
int main(int argc, char* argv[])
{
AutoSeededRandomPool prng;

SecByteBlock key[Blowfish::DEFAULT_KEYLENGTH];
prng.GenerateBlock( key, key.size() );

byte iv[ Blowfish::BLOCKSIZE ];
prng.GenerateBlock( iv, sizeof(iv) );

string ofilename = "puppy-and-teddy-orig.jpg";
string efilename = "puppy-and-teddy.enc";
string rfilename = "puppy-and-teddy-recovered.jpg";

try {

    /*********************************\
    \*********************************/

    EAX< Blowfish >::Encryption e1;
    e1.SetKeyWithIV(key, key.size(), iv, sizeof(iv));

    FileSource fs1(ofilename.c_str(), true,new AuthenticatedEncryptionFilter(e1,new FileSink(efilename.c_str())) );

    /*********************************\
    \*********************************/

    EAX< Blowfish >::Decryption d2;
    d2.SetKeyWithIV( key, key.size(), iv, sizeof(iv) );

    FileSource fs2(efilename.c_str(), true,new AuthenticatedDecryptionFilter( d2,new FileSink( rfilename.c_str() ),AuthenticatedDecryptionFilter::THROW_EXCEPTION) );

} catch (const Exception& ex) {
    cerr << ex.what() << endl;
}
}
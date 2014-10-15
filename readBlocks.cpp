// // read a file into memory
// #include <iostream>     // cout
// #include <fstream>      // ifstream
// using namespace std;

// int main () {

//   ifstream is ("notes", ifstream::binary);
//   if (is) 
//   {
//     // get length of file:
//     is.seekg (0, is.end);
//     int length = is.tellg();
//     is.seekg (0, is.beg);

//     char * buffer = new char [length];

//     cout << "Reading " << length << " characters... ";
//     // read data as a block:
//     is.read (buffer,length);

//     if (is)
//       cout << "all characters read successfully.";
//     else
//       cout << "error: only " << is.gcount() << " could be read";
//     is.close();

//     // ...buffer contains the entire file...

//     delete[] buffer;
//   }
//   return 0;
// }

// read a file into memory
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

int main () {
  std::ifstream is ("test.cpp", std::ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];

    // read data as a block:
    is.read (buffer,length);

    is.close();

    // print content:
    std::cout.write (buffer,length);

    delete[] buffer;
  }

  return 0;
}